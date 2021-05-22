#pragma once
#include "Entidad.h"
#include "../view/ComponenteVistaPolea.h"

class Polea : public Entidad {
    public:
        Polea(int x, int y, int direccion, SDL_Renderer *renderer);
        void mover();
        void mostrar(Uint32 frames);
    
    private:
        ComponenteVistaPolea* compVista;
};