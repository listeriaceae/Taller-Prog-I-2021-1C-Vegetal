#include "MarioState.h"
#include "SueloState.h"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"

const Stage *MarioState::stage{nullptr};

const MarioState *MarioState::resetPos(const float x, const float y, Mario &mario) const {
    mario.pos = {x, y};
    mario.estado = REPOSO;
    return SueloState::getInstance();
}

void MarioState::setStage(const Stage *stage_) {
    stage = stage_;
}