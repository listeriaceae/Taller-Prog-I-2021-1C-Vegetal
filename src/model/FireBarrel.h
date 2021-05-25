#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

class FireBarrel : public Entidad {
    public:
        FireBarrel(SDL_Renderer* renderer);
        void mover();
        void mostrar();
        virtual ~FireBarrel() {
            delete compVista;
        };

    private:
        ComponenteVistaEntidadEstatica* compVista;
};