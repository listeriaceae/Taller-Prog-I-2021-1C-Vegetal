#include "SueloState.h"
#include "AireState.h"
#include "TrepandoState.h"
#include "../../utils/Constants.hpp"

SueloState *SueloState::instance = NULL;

SueloState* SueloState::getInstance() {
    if (instance == NULL) {
        instance = new SueloState();
    }
    return instance;
}

MarioState* SueloState::handleInput(char controls) {

    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    velX = (right - left) * MARIO_VEL_X;

    char space = (controls & SPACE) != 0;
    if (space) {
        velY = MARIO_VEL_SALTO;
        estado = SALTANDO;
        return AireState::getInstance();
    }

    char up = (controls & UP) != 0;
    char down = (controls & DOWN) != 0;
    velY = (up - down) * MARIO_VEL_TREPAR;

    return instance;
}

MarioState* SueloState::update(float *x, float *y) {
    if (!stage->collide(x, y, &velX, &velY)) return AireState::getInstance();

    Ladder *ladder = stage->getLadder(*x, *y, velY);
    if (ladder != NULL && std::abs(ladder->getX() - *x) < 2) {
        *x = ladder->getX();
        TrepandoState *trepandoState = TrepandoState::getInstance();
        trepandoState->setLadder(ladder);
        return trepandoState;
    }

    *x += velX;
    *x -= (*x < 0 || *x > ANCHO_NIVEL - ANCHO_MARIO) * velX;
    estado = estado % 2 + (velX != 0.f) * CORRIENDO;
    return instance;
}