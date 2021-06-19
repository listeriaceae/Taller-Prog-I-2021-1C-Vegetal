#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include "../configuration.hpp"
#include "../logger.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Mario.hpp"
#include "../view/Nivel1Vista.h"
#include "../view/Nivel2Vista.h"
#include "../controller/MarioController.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"
#include "../utils/estadoNivel.h"
#include "../utils/marioStructs.h"
#include "../utils/punto.h"
#include <queue>
#include "Server.h"

pthread_mutex_t mutex;

typedef struct handleCommandArgs {
    std::queue<command_t*>* commands;
    int* clientSocket;
    Mario* mario;
} handleCommandArgs_t;

const int MAX_QUEUED_CONNECTIONS = 3;

Server::Server(char* port) {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(atoi(port));

    std::cout << "Aplicación iniciada en modo servidor en el puerto: " << port << std::endl;
}
int Server::startServer() {
    //socket
    int serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (serverSocket == -1)
        return -1;

    this->serverSocket = serverSocket;

    //bind
    int serverBind = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(serverBind < 0)
        return -1;

    //listen
    if (listen(serverSocket , MAX_QUEUED_CONNECTIONS) < 0)
        return -1;
    printf("listen...\n");
    //Accept
    while(clientSockets.size() < MAX_PLAYERS) {
        int client = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t*) &clientAddrLen);
        clientSockets.push_back(client);
        printf("Players: %d/%d\n", (int)clientSockets.size(), MAX_PLAYERS);
    }
    clientSocket = clientSockets.at(0);
    if (clientSocket < 0)
        return -1;
    printf("accept\n");
    startGame();

    close(clientSocket);
    close(serverSocket);  
    return 0;
}

void Server::startGame() {
    
    logger::Logger::getInstance().logNewGame();
    
    auto configuration = configuration::GameConfiguration(CONFIG_FILE);
    auto log_level = configuration.getLogLevel();
    logger::Logger::getInstance().setLogLevel(log_level);

    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_Window* window = SDL_CreateWindow(NOMBRE_JUEGO.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(NULL, -1, SDL_RENDERER_PRESENTVSYNC);
    
    std::vector<Mario*> marios;
    for(unsigned int i = 0; i < MAX_PLAYERS; i++) {
        marios.push_back(new Mario()); 
    }
    
    Uint8 currentLevel = 1;
    Nivel *nivel = NULL;
    NivelVista *vista = NULL;
    
    getNextLevel(&nivel, &vista, marios, &configuration, currentLevel, renderer);
    
    Uint32 previous, current, elapsed, lag;
    //bool updated, quitRequested = false;
    bool updated;
    previous = SDL_GetTicks();
    lag = 0;

    bool quitRequested = false;
    handleCommandArgs_t handleCommandArgs[MAX_PLAYERS];
    
    for(unsigned int i = 0; i < clientSockets.size(); i++) { //creo 1 hilo por cliente que recibe comandos y los coloca en una cola
        handleCommandArgs[i].commands = &(this->commands);
        handleCommandArgs[i].clientSocket = &(clientSockets[i]);
        handleCommandArgs[i].mario = marios[i];

        pthread_t recvCommandThread;
        pthread_create(&recvCommandThread, NULL, handleCommand, (void*)&handleCommandArgs[i]);
    }
    
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

        if(updated) {
            pthread_mutex_lock(&mutex);
            for(unsigned int i = 0; i < commands.size(); i++) {
                command_t* command = commands.front();
                commands.pop();
                command->mario->setEstado(*(command->controls));
            }
            pthread_mutex_unlock(&mutex);
            
            for(unsigned int i = 0; i < clientSockets.size(); i++) {
                estadoNivel_t* view = nivel->getEstado();
                sendView(&clientSockets[i], view);                 
            }
        }
        
        quitRequested = SDL_QuitRequested();
    }
}

void* Server::handleCommand(void* handleCommandArgs) {
    handleCommandArgs_t* args = (handleCommandArgs_t*)handleCommandArgs;
    controls_t controls;
    bool quitRequested = false;
    
    while(!quitRequested) {
        receiveCommand(args->clientSocket, &controls);
        //printf("command received: %d\n", (int)controls);
        command_t command;
        command.mario = args->mario;
        command.controls = &controls;

        pthread_mutex_lock(&mutex);
        args->commands->push(&command);
        pthread_mutex_unlock(&mutex);

        quitRequested = SDL_QuitRequested();
    }
}
int Server::sendView(int* clientSocket, estadoNivel_t* view) {
    int totalBytesSent = 0;
    int bytesSent = 0;
    int dataSize = sizeof(estadoNivel_t);
    bool clientSocketStillOpen = true;
    
    while((totalBytesSent < dataSize) && clientSocketStillOpen) {
        bytesSent = send(*clientSocket, (view + totalBytesSent), (dataSize - totalBytesSent), MSG_NOSIGNAL);
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

int Server::receiveCommand(int* clientSocket, controls_t* controls) {
    int totalBytesSent = 0;
    int bytesSent = 0;
    int dataSize = sizeof(controls_t);
    bool clientSocketStillOpen = true;
    
    while((totalBytesSent < dataSize) && clientSocketStillOpen) {
        bytesSent = recv(*clientSocket, (controls + totalBytesSent), (dataSize - totalBytesSent), MSG_NOSIGNAL);
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

void Server::getNextLevel(Nivel **nivel, NivelVista **vista, std::vector<Mario*> marios, configuration::GameConfiguration *config, Uint8 currentLevel, SDL_Renderer *renderer) {
    if (currentLevel == 1) {
        logger::Logger::getInstance().logInformation("Level 1 starts");

        Nivel1 *nivel1 = new Nivel1();
        
        for(int i = 0; i < MAX_PLAYERS; i++) {
            marios[i]->setPos(MARIO_START_X, MARIO_START_Y);
            nivel1->addPlayer(marios[i]);
        }
        
        auto enemies = config->getEnemies();
        for (auto enemy: enemies) {
            if (enemy.getType().compare("Fuego") == 0) nivel1->addEnemies(enemy.getQuantity());
            logger::Logger::getInstance().logDebug("Enemy type: " + enemy.getType());
            logger::Logger::getInstance().logDebug("Enemy quantity: " + std::to_string(enemy.getQuantity()));
        }
        
        *vista = new Nivel1Vista(renderer, config->getDefaultConfigFlag());
        (*vista)->addPlayers(MAX_PLAYERS);                                           // Aca iria cantidad de jugadores
        auto stages = config->getStages();
        if (stages.size() > 0) {
            std::string rutaImagen = stages[0].getBackgrounds()[0];
            logger::Logger::getInstance().logDebug("Stage 1 background img: " + rutaImagen);
            (*vista)->setBackground(rutaImagen);
        }
        
        *nivel = nivel1;
    }
    else if (currentLevel == 2) {
        logger::Logger::getInstance().logInformation("End of Level 1");
        logger::Logger::getInstance().logInformation("Level 2 starts");
        delete *nivel;
        *nivel = new Nivel2();
        
        for(int i = 0; i < MAX_PLAYERS; i++) {
            marios[i]->setPos(MARIO_START_X, MARIO_START_Y);
            (*nivel)->addPlayer(marios[i]);
        }

        delete *vista;
        *vista = new Nivel2Vista(renderer, config->getDefaultConfigFlag());
        (*vista)->addPlayers(MAX_PLAYERS);
        auto stages = config->getStages();
        if (stages.size() > 1) {
            std::string rutaImagen = stages[1].getBackgrounds()[0];
            logger::Logger::getInstance().logDebug("Stage 2 background img: " + rutaImagen);
            (*vista)->setBackground(rutaImagen);
        }
        return;
    } else {
        logger::Logger::getInstance().logInformation("End of Level 2");
        delete *nivel;
        delete *vista;
        //delete mario;
        *nivel = NULL;
    }
}