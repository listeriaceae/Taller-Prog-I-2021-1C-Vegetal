#pragma once
#include <SDL2/SDL.h>
#include "Entidad.h"
#include "Rendereable.h"
#include "ComponenteVistaFuego.h"

class Fuego : public Entidad, public Rendereable{
    public:
    
    Fuego(int posX, int posY, int ancho, int alto);

    void mostrar(SDL_Renderer* renderer);

    private:
    ComponenteVistaFuego* compVista;
};