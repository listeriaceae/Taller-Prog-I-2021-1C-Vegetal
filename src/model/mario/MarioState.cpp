#include "MarioState.h"

const Stage *MarioState::stage{nullptr};

void MarioState::setStage(const Stage *stage) {
    this->stage = stage;
}