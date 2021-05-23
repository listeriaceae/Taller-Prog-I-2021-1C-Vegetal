#pragma once

#include <SDL2/SDL.h>

#define ANCHO_PLATAFORMA 16
#define ALTO_PLATAFORMA 8

class ComponenteVistaPlataformaMovil {
    public:
        ComponenteVistaPlataformaMovil(float y, SDL_Renderer *renderer);
        void mover(float x);
        void mostrar(Uint32 frames);

    private:
        static SDL_Renderer *renderer;
        static SDL_Texture *texture;
        SDL_Rect rectDst; //Rectangulo que determina donde se va a renderear el objeto
};