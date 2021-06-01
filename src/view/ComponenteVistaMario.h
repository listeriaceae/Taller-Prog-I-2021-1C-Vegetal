#pragma once

#include <SDL2/SDL.h>

#define ANCHO_MARIO 16
#define ALTO_MARIO 16

class ComponenteVistaMario 
{
    public:
        ComponenteVistaMario(SDL_Renderer *renderer);
        void mostrar(float x, float y, char estado);
        void free();

    private:
        static SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Rect rectSrc; //Rectangulo que determina que parte de la imagen cargar
        SDL_Rect rectDst; //Rectangulo que determina donde se va a renderear el objeto
        SDL_RendererFlip flip;
        int tiempo;

        void updateReposo();
        void updateCorriendo(int next_x);
        void updateSaltando();
        void updateTrepando(int y);
};