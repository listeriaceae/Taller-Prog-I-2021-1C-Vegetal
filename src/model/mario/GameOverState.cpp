#include "GameOverState.h"
#include "../../utils/Constants.hpp"

GameOverState *GameOverState::instance = NULL;

GameOverState::GameOverState() {}

GameOverState *GameOverState::getInstance() {
    if (instance == NULL) {
        instance = new GameOverState();
    }
    return instance;
}

MarioState *GameOverState::update(Mario *mario) {
    mario->estado = DESCONECTADO;
    return instance;
}