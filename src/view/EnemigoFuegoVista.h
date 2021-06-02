#pragma once

#include <SDL2/SDL.h>
#include "../model/Entidad.h"

class EnemigoFuegoVista {
    public:
        EnemigoFuegoVista(SDL_Renderer *renderer);
        void setTotal(unsigned int n);
        void mover(punto_t pos);
        void mostrar();
        ~EnemigoFuegoVista();

    private:
        static SDL_Renderer *renderer;
        static SDL_Texture *texture;
        static SDL_Rect srcRect;
        static SDL_Rect dstRect;
        int tiempo;
        int totalEnemigos;
};