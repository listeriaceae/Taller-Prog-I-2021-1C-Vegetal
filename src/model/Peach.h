#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

class Peach : public Entidad {
    public:

        Peach(SDL_Renderer *renderer);
        void mover();
        void mostrar();
        virtual ~Peach() {
            delete compVista;
        };

    private:
        ComponenteVistaEntidadEstatica* compVista;
};