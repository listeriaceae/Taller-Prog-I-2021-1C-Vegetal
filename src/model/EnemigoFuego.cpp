#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "EnemigoFuego.h"

#define MAX_DESPLAZAMIENTO_PIXELES 10

EnemigoFuego::EnemigoFuego(float x, float y, int velX, SDL_Renderer *renderer)
: Entidad(x, y, ancho, alto) {
    this->velX = velX;
    this->posXInicial = posX;
    this->compVista = new ComponenteVistaEnemigoFuego(renderer);
}

void EnemigoFuego::mover() {
    posX += velX;
    if (abs(posX - posXInicial) > MAX_DESPLAZAMIENTO_PIXELES) velX *= -1; //cambio de dirección
}

void EnemigoFuego::mostrar(Uint32 frames) {
    compVista->mover(posX, posY);
    compVista->mostrar(frames);
}

std::string EnemigoFuego::getRutaImagen() {
    return compVista->getRutaImagen();
}