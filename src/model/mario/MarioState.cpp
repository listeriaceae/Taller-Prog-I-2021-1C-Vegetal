#include "MarioState.h"

const Stage *MarioState::stage{nullptr};

void MarioState::setStage(const Stage *stage_) {
    stage = stage_;
}