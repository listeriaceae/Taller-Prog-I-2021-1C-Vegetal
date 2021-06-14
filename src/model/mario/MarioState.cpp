#include "MarioState.h"
#include "../../utils/Constants.hpp"

Stage *MarioState::stage = NULL;
char MarioState::estado = REPOSO;
float MarioState::velX, MarioState::velY = 0.f;

MarioState::MarioState() {}

char MarioState::getEstado() {
    return estado;
}

void MarioState::setStage(Stage *stage) {
    this->stage = stage;
}