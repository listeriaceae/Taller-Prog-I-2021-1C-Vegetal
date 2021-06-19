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
    static int sendCommand(int* clientSocket, controls_t* command);
    static void* receiveDataThread(void* args);
    static void* sendDataThread(void* args);
    int clientSocket;
    struct sockaddr_in serverAddress;
    
};