#pragma once

#include <SDL2/SDL.h>
#include <arpa/inet.h>
#include "../utils/user.h"
#include "../view/SceneVista.h"

enum ClientExitStatus
{
    CLIENT_QUIT_REQUESTED,
    CLIENT_CONNECTION_CLOSED,
    CLIENT_GAME_OVER,
};

class Client
{
public:
    Client(char *serverIp, char *port);
    int startClient();
    int showStartPage();
    int connectToServer();
    ClientExitStatus startGame();
    int login(user_t user);

private:
    char *serverIp;
    char *port;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int clientSocket;
    struct sockaddr_in serverAddress;
    char name[4];
    void showConnectedPage();
    void getNextLevelView(SceneVista *&vista, unsigned char &clientScene, unsigned char serverScene);
    void processExit(ClientExitStatus clientExitStatus);
};