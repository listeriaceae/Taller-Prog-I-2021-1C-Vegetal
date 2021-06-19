#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <queue>

typedef struct command {
    controls_t* controls;
    Mario* mario;
} command_t;

class Server {
    public:
    Server(char* port);
    int startServer();
    
    private:
    std::queue<command_t*> commands;
    std::vector<int> clientSockets;
    void startGame();
    void getNextLevel(Nivel **nivel, NivelVista **vista, std::vector<Mario*> marios, configuration::GameConfiguration *config, Uint8 currentLevel, SDL_Renderer *renderer);
    static int sendView(int* clientSocket, estadoNivel_t* view);
    static int receiveCommand(int* clientSocket, controls_t* controls);
    static void* handleCommand(void* handleCommandArgs);
    static void* enviarVista(void* envioArgs);
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    int clientAddrLen;
};