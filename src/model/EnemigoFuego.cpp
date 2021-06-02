#include "EnemigoFuego.h"
#include "../utils/Constants.hpp"

#define MAX_DESPLAZAMIENTO 10

EnemigoFuego::EnemigoFuego(float x, float y, int velX)
: Entidad(x, y, ANCHO_ENEMIGO_FUEGO, ALTO_ENEMIGO_FUEGO) {
    this->velX = velX;
    this->posXInicial = posX;
}

void EnemigoFuego::mover() {
    posX += velX;
    velX -= 2 * velX * (abs(posX - posXInicial) > MAX_DESPLAZAMIENTO); //cambio de dirección
}