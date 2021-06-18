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

MarioState *SueloState::handleInput(controls_t controls, float *xSpeed, float *ySpeed) {
    *xSpeed = (controls.right - controls.left) * MARIO_VEL_X;
    if (controls.space) {
        *ySpeed = MARIO_VEL_SALTO;
        return AireState::getInstance();
    }
    *ySpeed = (controls.up - controls.down) * MARIO_VEL_TREPAR;

    return instance;
}

MarioState *SueloState::update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado) {
    Ladder *ladder = stage->getLadder(*x, *y, *ySpeed);
    if (ladder != NULL && std::abs(*x - (ladder->getX() - 4)) <= 4) {
        *x = ladder->getX() - 4;
        TrepandoState *trepandoState = TrepandoState::getInstance();
        trepandoState->setLadder(ladder);
        return trepandoState;
    }
    *x += *xSpeed * ((*x < ANCHO_NIVEL - ANCHO_MARIO && 0 < *xSpeed) || (0 < *x && *xSpeed < 0));
    *y -= GRAVEDAD;
    if (!stage->collide(x, y, xSpeed, ySpeed)) {
        *xSpeed = 0;
        *ySpeed = 0;
        return AireState::getInstance();
    }
    *estado = (*estado == DE_ESPALDAS) + (*xSpeed != 0) * (CORRIENDO - (*estado == DE_ESPALDAS));
    return instance;
}