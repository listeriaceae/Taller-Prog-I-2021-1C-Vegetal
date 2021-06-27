#pragma once

#include <SDL2/SDL.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <exception>
#include "../utils/estadoNivel.h"
#include "../utils/user.h"
#include <string>

class Client {
    public:
    Client(char* serverIp, char* port);
    int startClient();
    int showStartPage();
    int connectToServer();
    void startGame();
    int login(user_t user);

    private:
        char* serverIp;
        char* port;
        SDL_Window* window;
        SDL_Renderer* renderer;
        static void *sendDataThread(void* args);
        static int sendCommand(int clientSocket, controls_t* command);
        static void *receiveDataThread(void *args);
        static int receiveView(int clientSocket, estadoNivel_t* view);
        int clientSocket;
        struct sockaddr_in serverAddress;
        user_t user;
        int sendLoginRequest (user_t* user);
        int receiveLoginResponse (int* response);
        void showConnectedPage();
};