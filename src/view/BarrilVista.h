#pragma once

#include <SDL2/SDL.h>
#include "../model/Entidad.h"

class BarrilVista {
    public:
        BarrilVista(SDL_Renderer *renderer);
        void setTotal(unsigned int n);
        void mover(punto_t pos);
        void mostrar();
        ~BarrilVista();

    private:
        static SDL_Renderer *renderer;
        static SDL_Texture *texture;
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        int tiempo;
        int totalBarriles;
};