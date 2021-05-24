#pragma once
#include <SDL2/SDL.h>

#define ANCHO_FUEGO 16
#define ALTO_FUEGO 16

class ComponenteVistaFuego {
    public:
        ComponenteVistaFuego(int x, int y, SDL_Renderer* renderer);
        void mostrar();
    
    private:
        static SDL_Renderer* renderer;
        static SDL_Texture* texture;
        static SDL_Rect rectSrc; //Rectangulo que determina que parte de la imagen cargar
        static int tiempo;
        static int totalFuegos;
        static int fueActualizado;
        SDL_Rect rectDst; //Rectangulo que determina donde se va a renderear el objeto
};