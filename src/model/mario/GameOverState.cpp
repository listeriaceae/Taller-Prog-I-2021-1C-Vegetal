#include "GameOverState.h"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"


const GameOverState GameOverState::instance{};

const GameOverState *GameOverState::getInstance() {
    return &instance;
}

const MarioState *GameOverState::reset(float, float, Mario &) const {
    return this;
}

const MarioState *GameOverState::update(Mario &mario) const {
    mario.estado = GAME_OVER;
    return this;
}