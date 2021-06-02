#include "EnemigoFuego.h"
#include "../utils/Constants.hpp"

#define MAX_DESPLAZAMIENTO 10
#define ENEMIGO_FUEGO_VEL 0.25

EnemigoFuego::EnemigoFuego(punto_t pos, int direccion)
: Entidad(pos.x, pos.y, ANCHO_ENEMIGO_FUEGO, ALTO_ENEMIGO_FUEGO) {
    this->velX = direccion * ENEMIGO_FUEGO_VEL;
}

void EnemigoFuego::setLimites(float min, float max) {
    this->min = min;
    this->max = max - ancho;
}

void EnemigoFuego::mover() {
    posX += velX;
    velX -= 2 * velX * (posX < min || posX > max); //cambio de dirección
}