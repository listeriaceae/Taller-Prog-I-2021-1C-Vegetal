#include <string.h>
#include <iostream>
#include "model/Client.h"
#include "model/Server.h"

int main(int argc, char *argv[])
{
    if(argc == 3 && (strcmp(argv[1], "server") == 0)) {
        Server* server = new Server(argv[2]);
        server->startServer();
    } else if(argc == 4 && (strcmp(argv[1], "client") == 0)) {
        Client* client = new Client(argv[2], argv[3]);
        client->connectToServer();
        if (client->showStartPage() == 1) return 0;
        client->startGame();
    } else {
        std::cout << "ERROR: no es posible ejecutar el juego" << std::endl;
    }

    return 0;
}