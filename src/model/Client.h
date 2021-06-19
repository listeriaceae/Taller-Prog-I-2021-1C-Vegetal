#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../utils/estadoNivel.h"

class Client {
    public:
    Client();
    int connectToServer(char* serverIp, char* port);

    private:
    void startGame();
    static int receiveView(int clientSocket, estadoNivel_t* view);
    static void* sendDataThread(void* args);
    static int sendCommand(int clientSocket, controls_t* command);
    int clientSocket;
    struct sockaddr_in serverAddress;
};