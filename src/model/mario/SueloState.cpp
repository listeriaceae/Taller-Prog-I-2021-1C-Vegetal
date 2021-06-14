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

MarioState *SueloState::handleInput(char controls, float *xSpeed, float *ySpeed) {

    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    *xSpeed = (right - left) * MARIO_VEL_X;

    char space = (controls & SPACE) != 0;
    if (space) {
        *ySpeed = MARIO_VEL_SALTO;
        return AireState::getInstance();
    }

    char up = (controls & UP) != 0;
    char down = (controls & DOWN) != 0;
    *ySpeed = (up - down) * MARIO_VEL_TREPAR;

    return instance;
}

MarioState *SueloState::update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado) {
    Ladder *ladder = stage->getLadder(*x, *y, *ySpeed);
    if (ladder != NULL && std::abs(ladder->getX() - (*x + 4)) < 5) {
        *x = ladder->getX() - 4;
        TrepandoState *trepandoState = TrepandoState::getInstance();
        trepandoState->setLadder(ladder);
        return trepandoState;
    }
    *x += *xSpeed * ((*x < ANCHO_NIVEL - ANCHO_MARIO && 0 < *xSpeed) || (0 < *x && *xSpeed < 0));
    *y += 1;
    if (!stage->collide(x, y, xSpeed, ySpeed)) {
        *ySpeed = 0;
        return AireState::getInstance();
    }
    *estado = (*estado == DE_ESPALDAS) + (*xSpeed != 0) * (CORRIENDO - (*estado == DE_ESPALDAS));
    return instance;
}