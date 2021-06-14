#include "AireState.h"
#include "SueloState.h"
#include "../../utils/Constants.hpp"

#define GRAVEDAD - (MARIO_VEL_SALTO / 16)

AireState *AireState::instance = NULL;

AireState::AireState() {}

AireState *AireState::getInstance() {
    if (instance == NULL) {
        instance = new AireState();
    }
    return instance;
}

MarioState *AireState::handleInput(char) {
    return instance;
}

MarioState *AireState::update(float *x, float *y) {
    velX -= velX * 2 * !((*x < ANCHO_NIVEL - ANCHO_MARIO && 0 < velX) || (0 < *x && velX < 0));
    this->velY += GRAVEDAD;
    *x += velX;
    *y -= velY;
    if (stage->collide(x, y, &velX, &velY)) {
        estado = REPOSO;
        return SueloState::getInstance();
    }
    if (*y > ALTO_NIVEL - ALTO_MARIO) {
        *x = MARIO_START_X;
        *y = MARIO_START_Y;
        estado = REPOSO;
        return SueloState::getInstance();
    }
    estado = SALTANDO;
    return instance;
}