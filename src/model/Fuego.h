#pragma once
#include <SDL2/SDL.h>
#include "Entidad.h"
#include "../view/ComponenteVistaFuego.h"

class Fuego : public Entidad {
    public:
    
    Fuego(int posX, int posY, double resize, SDL_Renderer* renderer);
    void mover();
    void mostrar(Uint32 frames);
    void destruir();

    private:
    ComponenteVistaFuego* compVista;
};