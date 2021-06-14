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

MarioState *AireState::handleInput(char, float *, float *) {
    return instance;
}

MarioState *AireState::update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado) {
    *xSpeed -= *xSpeed * 2 * !((*x < ANCHO_NIVEL - ANCHO_MARIO && 0 < *xSpeed) || (0 < *x && *xSpeed < 0));
    *ySpeed += GRAVEDAD;
    *x += *xSpeed;
    *y -= *ySpeed;
    if (stage->collide(x, y, xSpeed, ySpeed)) {
        *estado = REPOSO;
        return SueloState::getInstance();
    }
    if (*y > ALTO_NIVEL - ALTO_MARIO) {
        *x = MARIO_START_X;
        *y = MARIO_START_Y;
        *estado = REPOSO;
        return SueloState::getInstance();
    }
    *estado = SALTANDO;
    return instance;
}