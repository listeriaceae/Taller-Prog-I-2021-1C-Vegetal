#pragma once

#include "EntidadEstaticaVista.h"

class PoleaVista : public EntidadEstaticaVista {
    public:
    
        PoleaVista(int x, int y, int orientation, int rotation, SDL_Renderer *renderer);
        void mostrar();
        ~PoleaVista();
    
    private:
        static SDL_Texture *texture;
        SDL_RendererFlip flip;
        static SDL_Rect rectSrc; //Rectangulo que determina que parte de la imagen cargar
        SDL_Rect rectDst; //Rectangulo que determina donde se va a renderear el objeto
        int tiempo;
        static int totalPoleas;
};