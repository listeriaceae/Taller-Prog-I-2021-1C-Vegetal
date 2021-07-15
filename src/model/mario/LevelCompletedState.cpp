#include "LevelCompletedState.h"
#include "../Mario.hpp"

const LevelCompletedState LevelCompletedState::instance{};

const LevelCompletedState *LevelCompletedState::getInstance() {
    return &instance;
}

const MarioState *LevelCompletedState::update(Mario &mario) const {
    mario.completeLevel();
    mario.estado = REPOSO;
    return this;
}