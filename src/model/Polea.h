#pragma once
#include "Entidad.h"
#include "../view/ComponenteVistaPolea.h"

class Polea : public Entidad {
    public:
        Polea(int x, int y, int direccion, int nivel, SDL_Renderer *renderer);
        void mover();
        void mostrar();
        virtual ~Polea() {
            delete compVista;
        };

    private:
        ComponenteVistaPolea* compVista;
};