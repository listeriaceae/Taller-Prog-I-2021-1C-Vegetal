#pragma once

#include "EntidadEstaticaVista.h"

class PeachVista : public EntidadEstaticaVista {
    public:
        PeachVista(SDL_Renderer* renderer);
        void mostrar();
        ~PeachVista() {
            SDL_DestroyTexture(texture);
        };

    private:
        static SDL_Texture* texture;
        SDL_Rect rect;
};