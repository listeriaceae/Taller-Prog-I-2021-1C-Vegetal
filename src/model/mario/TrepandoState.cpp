#include "SueloState.h"
#include "TrepandoState.h"
#include "../../utils/Constants.hpp"

TrepandoState *TrepandoState::instance = NULL;

TrepandoState* TrepandoState::getInstance() {
    if (instance == NULL) {
        instance = new TrepandoState();
    }
    return instance;
}

void TrepandoState::setLadder(Ladder *ladder) {
    this->ladder = ladder;
}

MarioState* TrepandoState::handleInput(char controls) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    velX = (right - left) * MARIO_VEL_X;

    char up = (controls & UP) != 0;
    char down = (controls & DOWN) != 0;
    velY = (up - down) * MARIO_VEL_TREPAR;

    return instance;
}

MarioState* TrepandoState::update(float *x, float *y) {
    if ((velY <= 0.f && std::abs(ladder->getBottom() - *y) <= 0.25f) ||
        (velY >= 0.f && std::abs(ladder->getTop() - *y) <= 0.25f))
    {
        velY = 0.f;
        estado = DE_ESPALDAS;
        return SueloState::getInstance();
    }
    *y -= velY;
    estado = TREPANDO;
    return instance;
}