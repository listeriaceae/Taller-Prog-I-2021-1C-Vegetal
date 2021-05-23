#include <SDL2/SDL.h>
#include <vector> 
#include "Barril.h"
#include "../utils/window.hpp"
#include <stdio.h>

#define VELOCIDAD_BARRIL 1

using namespace std;

Barril::Barril(float x, float y, SDL_Renderer *renderer)
: Entidad(x, y, ANCHO_BARRIL, ALTO_BARRIL) {
    this->velX = 0;
    this->velY = VELOCIDAD_BARRIL;
    compVista = new ComponenteVistaBarril(renderer);
}

void Barril::mover() {
    posY += velY;
}

bool Barril::estaEnNivel() {
    return (posY < ALTO_NIVEL);
}

void Barril::mostrar(Uint32 frames) {
    compVista->mover(posX, posY);
    compVista->mostrar(frames);
}