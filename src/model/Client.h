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
    ExitStatus startGame();
    int login(user_t user);

private:
    char *serverIp;
    char *port;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int clientSocket;
    struct sockaddr_in serverAddress;
    char name[4];
    void getSceneView(SceneVista *&vista, unsigned char serverScene);
    void processExit(ExitStatus clientExitStatus);
};