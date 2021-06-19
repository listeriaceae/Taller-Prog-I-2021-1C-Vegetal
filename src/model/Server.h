#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include "../utils/estadoNivel.h"

class Server {
    public:
    Server(char* port);
    int startServer();
    
    private:
    std::vector<int> clientSockets;
    void startGame();
    static int sendView(int clientSocket, estadoNivel_t* view);
    static int receiveCommand(int clientSocket, controls_t* controls);
    static void* handleCommand(void* handleCommandArgs);

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    int clientAddrLen;
};