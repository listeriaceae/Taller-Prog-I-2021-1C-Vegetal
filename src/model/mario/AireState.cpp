#include "AireState.h"
#include "SueloState.h"
#include "../../utils/Constants.hpp"

#define GRAVEDAD -0.03125

AireState *AireState::instance = NULL;

AireState* AireState::getInstance() {
    if (instance == NULL) {
        instance = new AireState();
    }
    return instance;
}

MarioState* AireState::handleInput(char controls) {
    return instance;
}

MarioState* AireState::update(float *x, float *y) {
    if (stage->collide(x, y, &velX, &velY)) return SueloState::getInstance();
    velX -= velX * 2 * (*x < 0 || *x > ANCHO_NIVEL - ANCHO_MARIO);
    this->velY += GRAVEDAD;
    *x += velX;
    *y -= velY;
    return instance;
}