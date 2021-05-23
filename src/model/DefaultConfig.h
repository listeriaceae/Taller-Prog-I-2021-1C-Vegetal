#pragma once

#include <string>
#include "Entidad.h"
#include "../view/DefaultConfigVista.h"

class DefaultConfig : public Entidad {
    public:
        DefaultConfig(SDL_Renderer *renderer);
        void mover();
        void mostrar(Uint32 frames);

    private:
        DefaultConfigVista *compVista;
};