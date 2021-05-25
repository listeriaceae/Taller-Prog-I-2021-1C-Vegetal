#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "EnemigoFuego.h"

#define MAX_DESPLAZAMIENTO_PIXELES 6

EnemigoFuego::EnemigoFuego(float x, float y, int velX, SDL_Renderer *renderer)
: Entidad(x, y - ALTO_ENEMIGO_FUEGO, ANCHO_ENEMIGO_FUEGO, ALTO_ENEMIGO_FUEGO) {
    this->velX = velX;
    this->posXInicial = posX;
    this->compVista = new ComponenteVistaEnemigoFuego(renderer);
}

void EnemigoFuego::mover() {
    posX += velX;
    if (abs(posX - posXInicial) > MAX_DESPLAZAMIENTO_PIXELES) velX *= -1; //cambio de dirección
}

void EnemigoFuego::mostrar() {
    compVista->mover(posX, posY);
    compVista->mostrar();
}