#include "SueloState.h"
#include "TrepandoState.h"
#include "../../utils/Constants.hpp"

TrepandoState *TrepandoState::instance = NULL;

TrepandoState::TrepandoState() {}

TrepandoState *TrepandoState::getInstance() {
    if (instance == NULL) {
        instance = new TrepandoState();
    }
    return instance;
}

void TrepandoState::setLadder(Ladder *ladder) {
    this->ladder = ladder;
}

MarioState *TrepandoState::update(Mario *mario) {
    mario->velY = (mario->controls.up - mario->controls.down) * MARIO_VEL_TREPAR;
    if ((mario->velY <= 0 && std::abs(ladder->getBottom() - mario->posY) <= MARIO_VEL_TREPAR / 2)
    || (mario->velY >= 0 && std::abs(ladder->getTop() - mario->posY) <= MARIO_VEL_TREPAR / 2))
    {
        mario->estado = DE_ESPALDAS;
        return SueloState::getInstance();
    }
    mario->posY -= mario->velY;
    mario->estado = TREPANDO;
    return instance;
}