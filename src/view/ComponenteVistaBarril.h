#pragma once

#include <SDL2/SDL.h>

#define ANCHO_BARRIL 12
#define ALTO_BARRIL 10

class ComponenteVistaBarril {
    public:
        ComponenteVistaBarril(SDL_Renderer *renderer);
        void mover(float x, float y);
        void mostrar(Uint32 frames);
        virtual ~ComponenteVistaBarril() {
            if (!(--totalBarriles)) {
                SDL_DestroyTexture(texture);
                texture = NULL;
            }
        };

    private:
        static SDL_Renderer *renderer;
        static SDL_Texture *texture;
        SDL_Rect rectSrc; //Rectangulo que determina que parte de la imagen cargar
        SDL_Rect rectDst; //Rectangulo que determina donde se va a renderear el objeto
        int tiempo;
        static int totalBarriles;
};