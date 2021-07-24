#pragma once

#include <SDL2/SDL.h>
#include <arpa/inet.h>
#include "../utils/user.h"
#include "../view/SceneVista.h"
#include "../utils/exitStatus.h"

class Client
{
public:
    Client(char *serverIp, char *port);
    ~Client();
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
    void getSceneView(SceneVista *&vista, unsigned char serverScene);
    void processExit(ClientExitStatus clientExitStatus);
};