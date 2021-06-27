#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include "../utils/estadoNivel.h"
#include "../configuration.hpp"
#include <queue>
#include <map>
#include "../utils/player.h"

class Server {
    public:
        Server(char* port);
        int startServer();
    
    private:
        unsigned int maxPlayers;
        int serverSocket;
        std::vector<int> clientSockets;
        void startGame(configuration::GameConfiguration config);
        static int sendView(int clientSocket, estadoNivel_t* view);
        static int receiveCommand(int clientSocket, controls_t* controls);
        static void* handleCommand(void* handleCommandArgs);
        static void* acceptNewConnections(void* server);
        struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
        int clientAddrLen;
        std::queue<int> clientSocketQueue;
        std::map<std::string, user_t> users;
        std::map<std::string, player_t> connectedPlayers;
        static void* handleLogin(void* arguments);
        int validateUserLogin(int client);
        static int receiveLoginRequest (int client, user_t* player);
        static int sendLoginResponse (int client, int* response);
        bool isFull();
};