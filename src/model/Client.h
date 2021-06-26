#pragma once

#include <SDL2/SDL.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../utils/estadoNivel.h"
#include "../utils/user.h"
#include <string>

class Client {
    public:
    Client(char* serverIp, char* port);
    int showStartPage();
    int connectToServer();
    void startGame();
    int z_login(std::string username, std::string password);

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
        int z_sendLogin (user_t* user);
        int z_receiveLoginResponse (int* response);
};