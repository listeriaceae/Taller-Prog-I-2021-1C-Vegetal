#pragma once
#include <SDL2/SDL.h>

#define ANCHO_ENEMIGO_FUEGO 15
#define ALTO_ENEMIGO_FUEGO 16

class ComponenteVistaEnemigoFuego {
    public:
        ComponenteVistaEnemigoFuego(SDL_Renderer *renderer);
        void mover(float x, float y);
        void mostrar(Uint32 frames);

    private:
        static SDL_Renderer *renderer;
        static SDL_Texture *texture;
        SDL_Rect rectSrc;
        SDL_Rect rectDst; //Rectangulo que determina donde se va a renderear el objeto
};