#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

class DonkeyKong : public Entidad {
    public:

        DonkeyKong(SDL_Renderer *renderer);
        void mover();
        void mostrar();
        virtual ~DonkeyKong() {
            delete compVista;
        };


    private:
        ComponenteVistaEntidadEstatica* compVista;
};