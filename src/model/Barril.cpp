#include <SDL2/SDL.h>
#include <stdexcept> 
#include "Barril.h"
#include "../utils/window.hpp"

using namespace std;

Barril::Barril(int posX, int posY)
: Entidad(posX, posY, 40, 40){
    this->velX = 0;
    this->velY = 0;
    compVista = new ComponenteVistaBarril();
}

void Barril::mover() {
    if((SDL_GetTicks() - tickUltimoMovimiento) < 60) //Solo se mueve cada 60 ticks
        return;
    
    posY += velY;

    if((posY < 0) || ((posY + alto) > ALTO_PANTALLA)) {
        throw out_of_range ("El barril termino su recorrido");
    }

    tickUltimoMovimiento = SDL_GetTicks();
}

void Barril::mostrar() {
    compVista->mostrar();
}