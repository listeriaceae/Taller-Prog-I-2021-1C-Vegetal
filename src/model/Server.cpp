#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include "../configuration.hpp"
#include "../logger.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "../utils/Messages.h"
#include "../utils/window.hpp"
#include "../utils/estadoNivel.h"
#include "Server.h"
#include <queue>
#include <vector>
#include "../logger.h"
#include "string"
#include "../utils/player.h"

typedef struct handleLoginArgs {
    Server* server;
    int clientId;
} handleLoginArgs_t;

typedef struct handleCommandArgs {
    int clientSocket;
    Mario* mario;
    Server* server;
} handleCommandArgs_t;

void getNextLevel(Nivel **nivel, configuration::GameConfiguration *config, Uint8 currentLevel);

const int MAX_QUEUED_CONNECTIONS = 3;

Server::Server(char* port) {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(atoi(port));

    std::cout << "Aplicación iniciada en modo servidor en el puerto: " << port << std::endl;

    logger::Logger::getInstance().logInformation("Loading valid users...");
    auto config = configuration::GameConfiguration(CONFIG_FILE);
    for (auto u: config.getUsers())
    {
        this->users[u.username] = u;
        logger::Logger::getInstance().logDebug(std::string("user: ") + u.username + " " + u.password);
    }
}

int Server::startServer() {
    auto config = configuration::GameConfiguration(CONFIG_FILE);
    auto logLevel = config.getLogLevel();
    logger::Logger::getInstance().setLogLevel(logLevel);

    this->maxPlayers = config.getMaxPlayers();
    if(this->maxPlayers < 1) {
        logger::Logger::getInstance().logDebug(CANTIDAD_DE_JUGADORES_INVALIDA);
        this->maxPlayers = DEFAULT_MAX_PLAYERS;
    }

    //socket
    serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (serverSocket == -1) {
        return -1;
    }

    //bind
    int serverBind = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(serverBind < 0) {
        return -1;
    }

    //listen
    if (listen(serverSocket , MAX_QUEUED_CONNECTIONS) < 0) {
        return -1;
    }

    pthread_t acceptConnectionsThread;
    pthread_create(&acceptConnectionsThread, NULL, acceptNewConnections, this);

    printf("listening...\n");

    while(this->connectedPlayers.size() < (unsigned int)maxPlayers) {}

    printf("Accept\n");

    startGame(config);

    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}

bool Server::isFull() {
    return (this->connectedPlayers.size() == this->maxPlayers);
}

void* Server::acceptNewConnections(void* serverArg) {
    Server* server = (Server*)serverArg;
    
    while(true) {
        int client = accept(server->serverSocket, (struct sockaddr *)&(server->clientAddress), (socklen_t*) &(server->clientAddrLen));
        server->clientSocketQueue.push(client);
        server->clientSockets.push_back(client);
        
        printf("Players: %d/%d\n", (int)server->clientSockets.size(), server->maxPlayers);

        if(server->isFull()) {
            std::cout << "Cantidad de jugadores excedida" << std::endl;
            close(client);
            return NULL;
        }

        handleLoginArgs_t arguments;
        arguments.clientId = client;
        arguments.server = server;

        pthread_t clientConnection;

        logger::Logger::getInstance().logInformation(std::string("Creating login thread for clientI: ") + std::to_string(client));
        pthread_create(&clientConnection, NULL, handleLogin, &arguments);
        
        //TODO: si el usuario ya esta en la lista de conexiones se actualiza el socket
        // if (server->clientSocketQueue.size() >= 1) {
        //     printf("Cantidad de jugadores excedida: en cola de espera\n");
        // }

        //close(client);
    }
}

void Server::startGame(configuration::GameConfiguration config) {   
    srand(time(NULL));
    SDL_Init(SDL_INIT_TIMER);

    std::vector<Mario*> players;
    for(unsigned int i = 0; i < (unsigned int)maxPlayers; ++i) {
        players.push_back(new Mario());
    }

    Uint8 currentLevel = 0;
    Nivel *nivel = NULL;

    getNextLevel(&nivel, &config, ++currentLevel);
    nivel->addPlayers(&players);

    handleCommandArgs_t handleCommandArgs[maxPlayers];

    for(unsigned int i = 0; i < this->clientSockets.size(); ++i) {
        // Dejo esta linea comentada
        // asi se asignaban antes los clientes
        // handleCommandArgs[i].clientSocket = clientSockets[i];
        handleCommandArgs[i].clientSocket = this->clientSocketQueue.front();
        this->clientSocketQueue.pop();
        handleCommandArgs[i].mario = players[i];
        handleCommandArgs[i].server = this;

        pthread_t recvCommandThread;
        pthread_create(&recvCommandThread, NULL, handleCommand, &handleCommandArgs[i]);
    }

    Uint32 previous, current, elapsed, lag;
    bool updated, quitRequested = false;
    previous = SDL_GetTicks();
    lag = 0;
    while(!quitRequested) {
        current = SDL_GetTicks();
        elapsed = current - previous;
        previous = current;
        lag += elapsed;
    
        // Update Model
        updated = false;
        while (lag >= MS_PER_UPDATE) {
            nivel->update();
            lag -= MS_PER_UPDATE;
            updated = true;
        }

        if (updated) {
            estadoNivel_t* view = nivel->getEstado();
            for(unsigned int i = 0; i < clientSockets.size(); i++){
                sendView(clientSockets[i], view);
            }
            
            if (nivel->isComplete()) {
                getNextLevel(&nivel, &config, ++currentLevel);
                if (nivel == NULL) {
                    break;
                }
                nivel->addPlayers(&players);
            }
        }
        quitRequested = SDL_QuitRequested();
    }
}

void *Server::handleCommand(void *handleCommandArgs) {
    Mario *mario = ((handleCommandArgs_t *)handleCommandArgs)->mario;
    int clientSocket = ((handleCommandArgs_t *)handleCommandArgs)->clientSocket;
    Server* server = ((handleCommandArgs_t *)handleCommandArgs)->server;

    controls_t controls;
    int bytesReceived;

    bool quitRequested = false;
    while(!quitRequested) {
        bytesReceived = receiveCommand(clientSocket, &controls);
        if (bytesReceived == sizeof(controls_t)) {
            mario->setControls(controls);
        } else {
            mario->disable();

            if(!server->clientSocketQueue.empty()) {
                printf("Reconectando...\n");
                clientSocket = server->clientSocketQueue.front();
                server->clientSockets.push_back(server->clientSocketQueue.front());
                server->clientSocketQueue.pop();

                mario->enable();
            }
        }

        quitRequested = SDL_PeepEvents(NULL, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
    }
    return NULL;
}

int Server::sendView(int clientSocket, estadoNivel_t* view) {
    size_t totalBytesSent = 0;
    int bytesSent = 0;
    size_t dataSize = sizeof(estadoNivel_t);
    bool clientSocketStillOpen = true;
    
    while((totalBytesSent < dataSize) && clientSocketStillOpen) {
        bytesSent = send(clientSocket, (view + totalBytesSent), (dataSize - totalBytesSent), MSG_NOSIGNAL);
        if(bytesSent < 0) {
            return bytesSent;
        } 
        else if(bytesSent == 0) {
            clientSocketStillOpen = false;
        }
        else {
            totalBytesSent += bytesSent;
        }
    }

    return totalBytesSent;
}

int Server::receiveCommand(int clientSocket, controls_t* controls) {
    size_t totalBytesSent = 0;
    int bytesSent = 0;
    size_t dataSize = sizeof(controls_t);
    bool clientSocketStillOpen = true;
    
    while((totalBytesSent < dataSize) && clientSocketStillOpen) {
        bytesSent = recv(clientSocket, (controls + totalBytesSent), (dataSize - totalBytesSent), MSG_NOSIGNAL);
        if(bytesSent < 0) {
            return bytesSent;
        } 
        else if(bytesSent == 0) {
            clientSocketStillOpen = false;
        }
        else {
            totalBytesSent += bytesSent;
        }
    }

    return totalBytesSent;
}

void getNextLevel(Nivel **nivel, configuration::GameConfiguration *config, Uint8 currentLevel) {
    delete *nivel;
    if (currentLevel == 1) {
        logger::Logger::getInstance().logInformation("Level 1 starts");

        Nivel1 *nivel1 = new Nivel1();

        auto enemies = config->getEnemies();
        for (auto enemy: enemies) {
            if (enemy.getType().compare("Fuego") == 0) nivel1->addEnemies(enemy.getQuantity());
            logger::Logger::getInstance().logDebug("Enemy type: " + enemy.getType());
            logger::Logger::getInstance().logDebug("Enemy quantity: " + std::to_string(enemy.getQuantity()));
        }
        *nivel = nivel1;
    }
    else if (currentLevel == 2) {
        logger::Logger::getInstance().logInformation("End of Level 1");
        *nivel = new Nivel2();
        logger::Logger::getInstance().logInformation("Level 2 starts");
    }
    else {
        logger::Logger::getInstance().logInformation("End of Level 2");
        *nivel = NULL;
    }
}

// LOGIN
void * Server::handleLogin (void* arguments) {
    Server* server = ((handleLoginArgs_t*)arguments)->server;
    int client = ((handleLoginArgs_t*)arguments)->clientId;
    
    int response;

    do {
        std::cout << "LOOP server login" << std::endl;
        response = server->validateUserLogin(client);
    } while(response != LOGIN_OK && response != LOGIN_ABORTED);

    if(response == LOGIN_ABORTED) {
        std::cout << "Se detecto la desconexion" << std::endl;
        close(client);
        // TODO: borrar el client de clientSockets
        return NULL;
    }
    
    std::cout << "Jugador conectado" << std::endl;
    return NULL;
}

int Server::validateUserLogin(int client) {
    std::cout << "server login" << std::endl;
    user_t user;
    int bytesReceived = receiveLoginRequest(client, &user);
    std::cout << "bytes received: " << bytesReceived << std::endl;
    std::cout << "user: " << user.username << " " << user.password << std::endl;

    if(bytesReceived == 0) {
        // Desconexion del cliente
        return LOGIN_ABORTED;
    }

    int response;
    
    if (this->users.count(user.username) == 0) {
        logger::Logger::getInstance().logDebug(std::string("[") + user.username + "] invalid user");
        response = LOGIN_INVALID_USER;
        sendLoginResponse(client, &response);
        return LOGIN_INVALID_USER;
    } 
    
    auto existingUser = this->users.at(user.username);

    if (strcmp(existingUser.password, user.password) != 0) {
        logger::Logger::getInstance().logDebug(std::string("[") + user.username + "] incorrect password");
        response = LOGIN_INVALID_USER_PASS;
        sendLoginResponse(client, &response);
        return LOGIN_INVALID_USER_PASS;
    }

    if(this->connectedPlayers.count(user.username) != 0) {
        logger::Logger::getInstance().logDebug(std::string("[") + user.username + "] user already connected");
        response = LOGIN_USER_ALREADY_CONNECTED;
        sendLoginResponse(client, &response);
        return LOGIN_USER_ALREADY_CONNECTED;
    }

    std::cout << "LOGIN_OK" << std::endl;
    response = LOGIN_OK;
    sendLoginResponse(client, &response);

    // Usuario valido: login OK
    // Lo agrego a jugadores conectados
    player_t newPlayer;
    newPlayer.user = user;
    newPlayer.clientId = client;
    this->connectedPlayers[user.username] = newPlayer;
    return LOGIN_OK;
}

int Server::receiveLoginRequest (int client, user_t* user) {
    int totalBytesReceived = 0;
    int bytesReceived = 0;
    int dataSize = sizeof(user_t);
    bool clientSocketStillOpen = true;
    
    while((totalBytesReceived < dataSize) && clientSocketStillOpen) {
        bytesReceived = recv(client, (user + totalBytesReceived), (dataSize - totalBytesReceived), MSG_NOSIGNAL);
        if(bytesReceived < 0) {
            return bytesReceived;
        } 
        else if(bytesReceived == 0) {
            clientSocketStillOpen = false;
        }
        else {
            totalBytesReceived += bytesReceived;
        }
    }
    return totalBytesReceived;
}

int Server::sendLoginResponse (int client, int* response) {
    int totalBytesSent = 0;
    int bytesSent = 0;
    int dataSize = sizeof(int);
    bool clientSocketStillOpen = true;
    
    while((totalBytesSent < dataSize) && clientSocketStillOpen) {
        bytesSent = send(client, (response + totalBytesSent), (dataSize - totalBytesSent), MSG_NOSIGNAL);
        if(bytesSent < 0) {
            return bytesSent;
        } 
        else if(bytesSent == 0) {
            clientSocketStillOpen = false;
        }
        else {
            totalBytesSent += bytesSent;
        }
    }
    return totalBytesSent;
}