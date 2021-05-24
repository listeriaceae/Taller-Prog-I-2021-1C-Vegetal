#pragma once

#include <SDL2/SDL.h>

#define ANCHO_POLEA 11
#define ALTO_POLEA 10

class ComponenteVistaPolea {
    public:
    
        ComponenteVistaPolea(int x, int y, int direccion, int nivel, SDL_Renderer *renderer);
        void mostrar();
    
    private:
        static SDL_Renderer *renderer;
        static SDL_Texture *texture;
        SDL_RendererFlip flip;
        static SDL_Rect rectSrc; //Rectangulo que determina que parte de la imagen cargar
        SDL_Rect rectDst; //Rectangulo que determina donde se va a renderear el objeto
        static int tiempo;
        static int fueActualizado;
        static int totalPoleas;
};