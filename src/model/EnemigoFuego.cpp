#include "EnemigoFuego.h"
#include "../utils/Constants.hpp"

#define ENEMIGO_FUEGO_VEL 0.5f

EnemigoFuego::EnemigoFuego(punto_t pos, const int direccion, const float min, const float max)
: Entidad(pos.x, pos.y, ANCHO_ENEMIGO_FUEGO, ALTO_ENEMIGO_FUEGO),
velX(direccion * ENEMIGO_FUEGO_VEL), min(min - ancho / 2), max(max - ancho / 2) {}

void EnemigoFuego::mover() {
    velX -= 2 * velX * (pos.x < min || pos.x > max);
    pos.x += velX;
}