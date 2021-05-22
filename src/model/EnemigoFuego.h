#pragma once
#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEnemigoFuego.h"

class EnemigoFuego : public Entidad{
    public: 
    EnemigoFuego(float x, float y, int velX, SDL_Renderer *renderer);
    void mover();
    void mostrar(Uint32 frames);
    std::string getRutaImagen();

    private: 
    ComponenteVistaEnemigoFuego* compVista;
    int velX;
    int posXInicial;
};