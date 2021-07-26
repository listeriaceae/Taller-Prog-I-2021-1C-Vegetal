#include "EnemigoFuego.h"
#include "../utils/Constants.hpp"

#define ENEMIGO_FUEGO_VEL 0.5f

#define FUEGO_X_DIF 2.f
#define FUEGO_Y_DIF 8.f

const unsigned char FUEGO_POINTS = 10; // Cada enemigo destruido del tipo 2 otorga 1000 puntos

EnemigoFuego::EnemigoFuego(punto_t pos, const int direccion, const float min, const float max)
: Enemy(pos.x, pos.y), velX(direccion * ENEMIGO_FUEGO_VEL), min(min - ANCHO_ENEMIGO_FUEGO / 2), max(max - ANCHO_ENEMIGO_FUEGO / 2) {}

void EnemigoFuego::mover() {
    velX -= 2 * velX * (pos.x < min || pos.x > max);
    pos.x += velX;
}

dimensiones_t EnemigoFuego::dimensions() const {
    return {pos.x + FUEGO_X_DIF, pos.y + FUEGO_Y_DIF, pos.x + (ANCHO_ENEMIGO_FUEGO - FUEGO_X_DIF), pos.y + ALTO_ENEMIGO_FUEGO};
}

unsigned char EnemigoFuego::getPoints() {
    return FUEGO_POINTS;
}