#include "GameOverState.h"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"

const GameOverState *GameOverState::getInstance() {
    static const GameOverState instance;
    return &instance;
}

const MarioState *GameOverState::update(Mario &mario) const {
    mario.pos = {248, 128};
    return this;
}