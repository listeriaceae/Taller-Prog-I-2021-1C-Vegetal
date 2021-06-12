#include "MarioState.h"
#include "../../utils/Constants.hpp"

float MarioState::velX, MarioState::velY = 0.f;
char MarioState::estado = REPOSO;

char MarioState::getEstado() {
    return estado;
}