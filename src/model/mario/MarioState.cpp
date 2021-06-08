#include "MarioState.h"
#include <string>

MarioState::MarioState() {
    this->velX = 0.;
    this->velY = 0.;
}

std::string MarioState::getName() {
    return this->name;
}