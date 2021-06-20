#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <pthread.h>
#include <string>
#include "../view/Nivel1Vista.h"
#include "../view/Nivel2Vista.h"
#include "../controller/MarioController.h"
#include "../configuration.hpp"
#include "../logger.h"
#include "../utils/window.hpp"
#include "../utils/Constants.hpp"
#include "Client.h"

Client::Client() {
    std::cout << "Aplicación iniciada en modo cliente" << std::endl;
}

int Client::connectToServer(char* serverIp, char* port) {
    std::cout << "Intento conectarme al servidor en: " << serverIp << " en el puerto: " << port << std::endl;

    //socket
    clientSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (clientSocket == -1)
        return -1;

    serverAddress.sin_addr.s_addr = inet_addr(serverIp);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons( atoi(port));

    std::cout << "pre connect" << std::endl;
    //connect
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in)) < 0) {
        printf("error\n");
        return -1;
    }
    std::cout << "post connect" << std::endl;
    startGame();  
    
    return 1;
}

void Client::startGame() {
    logger::Logger::getInstance().logNewGame();
    
    auto configuration = configuration::GameConfiguration(CONFIG_FILE);
    auto log_level = configuration.getLogLevel();
    logger::Logger::getInstance().setLogLevel(log_level);

    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(NOMBRE_JUEGO.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    NivelVista *vista = NULL;
    
    vista = new Nivel1Vista(renderer, configuration.getDefaultConfigFlag());
    vista->addPlayers(MAX_PLAYERS);                                           // Aca iria cantidad de jugadores
    auto stages = configuration.getStages();
    if (stages.size() > 0) {
        std::string rutaImagen = stages[0].getBackgrounds()[0];
        logger::Logger::getInstance().logDebug("Stage 1 background img: " + rutaImagen);
        vista->setBackground(rutaImagen);
    }

    pthread_t sendThread;
    pthread_create(&sendThread, NULL, sendDataThread, &clientSocket);

    estadoNivel_t estadoNivel;
    int bytesReceived;

    bool quitRequested = false;
    while(!quitRequested) {
        bytesReceived = receiveView(clientSocket, &estadoNivel);
        if (bytesReceived == sizeof(estadoNivel_t)) {
            SDL_RenderClear(renderer);
            vista->update(&estadoNivel);
            SDL_RenderPresent(renderer);
        }
        quitRequested = SDL_QuitRequested();
    }

    logger::Logger::getInstance().logInformation("Game over");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void* Client::sendDataThread(void *args) {
    int clientSocket = *(int *)args;
    controls_t controls = getControls();

    bool quitRequested = false;
    while(!quitRequested) {
        if(*reinterpret_cast<char *>(&controls) != *reinterpret_cast<char *>(&(controls = getControls())))
            sendCommand(clientSocket, &controls);
        quitRequested = SDL_PeepEvents(NULL, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
    }
    return NULL;
}

int Client::sendCommand(int clientSocket, controls_t* controls) {
    size_t totalBytesSent = 0;
    int bytesSent = 0;
    size_t dataSize = sizeof(controls_t);
    bool clientSocketStillOpen = true;
    
    while((totalBytesSent < dataSize) && clientSocketStillOpen) {
        bytesSent = send(clientSocket, (controls + totalBytesSent), (dataSize - totalBytesSent), MSG_NOSIGNAL);
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

int Client::receiveView(int clientSocket, estadoNivel_t* view) {
    size_t totalBytesReceived = 0;
    int bytesReceived = 0;
    size_t dataSize = sizeof(estadoNivel_t);
    bool clientSocketStillOpen = true;

    while((totalBytesReceived < dataSize) && clientSocketStillOpen) {
        bytesReceived = recv(clientSocket, (view + totalBytesReceived), (dataSize - totalBytesReceived), MSG_NOSIGNAL);
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