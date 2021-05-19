#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaPolea.h"

class Polea : public Entidad{
    public:
    
    Polea(int posX, int posY, int ancho, int alto, std::string direccion);

    void mostrar(SDL_Renderer* renderer);

    void mover();
    
    private:
    ComponenteVistaPolea* compVista;
};