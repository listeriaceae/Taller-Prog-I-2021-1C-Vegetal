#pragma once
#include <arpa/inet.h>
#include <map>
#include "../utils/player.h"

class Server
{
public:
    Server(char *port);
    int startServer();

    std::map<std::string, user_t> users;
    unsigned int maxPlayers;
    int serverSocket;
    std::map<std::string, player_t *> connectedPlayers;

private:
    void startGame();

    struct sockaddr_in serverAddress;
};