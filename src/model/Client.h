#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>

class Client {
    public:
    Client();
    int connectToServer(char* serverIp, char* port);

    private:
    void startGame();
    static int receiveView(int* clientSocket, estadoNivel_t* view);
    static int sendCommand(int* clientSocket, char* command);
    static void* updateView(void* args);
    static void* handleCommand(void* args);
    int clientSocket;
    struct sockaddr_in serverAddress;
    
};