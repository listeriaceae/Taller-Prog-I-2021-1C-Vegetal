#pragma once
#include <SDL2/SDL.h>

class Rendereable {
    public:
    virtual void mostrar(SDL_Renderer* rendereable) = 0;
};