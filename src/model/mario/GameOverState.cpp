#include "GameOverState.h"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"


const GameOverState GameOverState::instance{};

const GameOverState *GameOverState::getInstance() {
    return &instance;
}

const MarioState *GameOverState::update(Mario &mario) const {
    mario.pos = {248, 128};
    return this;
}