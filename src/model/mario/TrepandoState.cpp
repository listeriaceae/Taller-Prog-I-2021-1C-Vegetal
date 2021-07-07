#include "SueloState.h"
#include "TrepandoState.h"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"

const TrepandoState *TrepandoState::getInstance() {
    static const TrepandoState instance;
    return &instance;
}

const MarioState *TrepandoState::update(Mario &mario) const {
    mario.velY = (mario.controls.up - mario.controls.down) * MARIO_VEL_TREPAR;
    if (mario.climbMin < mario.pos.y || mario.pos.y < mario.climbMax)
    {
        mario.estado = DE_ESPALDAS;
        return SueloState::getInstance();
    }
    mario.pos.y -= mario.velY;
    mario.estado = TREPANDO;
    return this;
}