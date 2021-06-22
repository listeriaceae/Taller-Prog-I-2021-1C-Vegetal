#include "DisabledState.h"
#include "SueloState.h"
#include "../../utils/Constants.hpp"

DisabledState *DisabledState::instance = NULL;

DisabledState::DisabledState() {}

DisabledState* DisabledState::getInstance() {
    if (instance == NULL) {
        instance = new DisabledState();
    }
    return instance;
}

MarioState *DisabledState::update(float *x, float *y, float *, float *, char *estado, controls_t) {
    // Al deshabilitar, vuelvo a Mario a la pos inicial
    *x = MARIO_START_X;
    *y = MARIO_START_Y;

    *estado = DESCONECTADO;
    return instance;
}