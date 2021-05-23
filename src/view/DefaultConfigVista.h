#pragma once

#include <SDL2/SDL.h>

#define DEFAULT_CONFIG_X 56
#define DEFAULT_CONFIG_Y 20
#define ANCHO_DEFAULT_CONFIG 108
#define ALTO_DEFAULT_CONFIG 7

class DefaultConfigVista {
    public:
        DefaultConfigVista(SDL_Renderer *renderer);
        void mostrar(Uint32 frames);
    
    private:
        static SDL_Texture *texture;
        static SDL_Renderer *renderer;
        static SDL_Rect rect;
        static Uint32 frames;
};