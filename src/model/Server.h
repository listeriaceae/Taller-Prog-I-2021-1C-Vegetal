#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>

class Server {
    public:
    Server(char* port);
    int startServer();
    
    private:
    std::vector<int> clientSockets;
    void startGame();
    void getNextLevel(Nivel **nivel, NivelVista **vista, std::vector<Mario*> marios, configuration::GameConfiguration *config, Uint8 currentLevel, SDL_Renderer *renderer);
    static int sendView(int* clientSocket, estadoNivel_t* view);
    static int receiveCommand(int* clientSocket, char* command);
    static void* handleCommand(void* handleCommandArgs);
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    int clientAddrLen;
};