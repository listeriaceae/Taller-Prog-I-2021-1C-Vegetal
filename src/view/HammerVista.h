#pragma once

#include <SDL2/SDL.h>
#include "../utils/punto.h"

class HammerVista
{
public:
    HammerVista(SDL_Renderer *renderer);
    void mover(punto_t pos);
    void mostrar();
    ~HammerVista();

private:
    static SDL_Renderer *renderer;
    static SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

};