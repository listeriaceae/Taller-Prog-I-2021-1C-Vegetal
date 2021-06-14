#include "MarioState.h"
#include "../../utils/Constants.hpp"

Stage *MarioState::stage = NULL;

MarioState::MarioState() {}

void MarioState::setStage(Stage *stage) {
    this->stage = stage;
}