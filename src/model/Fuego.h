#pragma once
#include <SDL2/SDL.h>
#include "Entidad.h"
#include "../view/ComponenteVistaFuego.h"

class Fuego : public Entidad {
    public:
    
    Fuego(int posX, int posY, SDL_Renderer* renderer);
    void mover();
    void mostrar();
    virtual ~Fuego() {
        delete compVista;
    }

    private:
    ComponenteVistaFuego* compVista;
};