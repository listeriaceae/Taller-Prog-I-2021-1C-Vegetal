#include "MarioState.h"
#include "SueloState.h"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"

Stage *MarioState::stage{nullptr};

const MarioState *MarioState::reset(Mario &mario) const {
    mario.pos = {MARIO_START_X, MARIO_START_Y};
    mario.estado = REPOSO;
    return SueloState::getInstance();
}

void MarioState::setStage(Stage *stage_) {
    stage = stage_;
}