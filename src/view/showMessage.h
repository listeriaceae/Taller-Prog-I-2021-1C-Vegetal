#pragma once
#include <SDL2/SDL.h>

namespace showMessage {
    void waitingLobby(SDL_Renderer *renderer);
    void disconnection(SDL_Renderer *renderer);
    void gameOver(SDL_Renderer *renderer);
    void gameComplete(SDL_Renderer *renderer);
}