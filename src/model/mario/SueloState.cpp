#include "SueloState.h"
#include "AireState.h"
#include "TrepandoState.h"
#include "../../utils/Constants.hpp"

SueloState *SueloState::instance = NULL;

SueloState::SueloState() {}

SueloState *SueloState::getInstance() {
    if (instance == NULL) {
        instance = new SueloState();
    }
    return instance;
}

MarioState *SueloState::handleInput(char controls) {

    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    velX = (right - left) * MARIO_VEL_X;

    char space = (controls & SPACE) != 0;
    if (space) {
        velY = MARIO_VEL_SALTO;
        return AireState::getInstance();
    }

    char up = (controls & UP) != 0;
    char down = (controls & DOWN) != 0;
    velY = (up - down) * MARIO_VEL_TREPAR;

    return instance;
}

MarioState *SueloState::update(float *x, float *y) {
    Ladder *ladder = stage->getLadder(*x, *y, velY);
    if (ladder != NULL && std::abs(ladder->getX() - (*x + 4)) < 5) {
        *x = ladder->getX() - 4;
        TrepandoState *trepandoState = TrepandoState::getInstance();
        trepandoState->setLadder(ladder);
        return trepandoState;
    }
    *x += ((*x < ANCHO_NIVEL - ANCHO_MARIO && 0 < velX) || (0 < *x && velX < 0)) * velX;
    *y += 1;
    if (!stage->collide(x, y, &velX, &velY)) {
        velY = 0;
        return AireState::getInstance();
    }
    estado = (estado == DE_ESPALDAS) + (velX != 0) * (CORRIENDO - (estado == DE_ESPALDAS));
    return instance;
}