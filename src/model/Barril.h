#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

class Barril : public Entidad {
public:

    static const int alto = 40;
    static const int ancho = 40;

    Barril(int posX, int posY, int velX, int velY);
    void mover();
    void mostrar(SDL_Renderer* renderer);
private:
    ComponenteVistaEntidadEstatica* compVista = new ComponenteVistaEntidadEstatica();
    std::string rutaImagen = "res/Barril.bmp";
    Uint32 tickUltimoMovimiento = 0;
    int velX = 0;
    int velY = 0;
};