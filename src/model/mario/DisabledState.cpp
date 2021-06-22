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

MarioState *DisabledState::update(float *, float *, float *xSpeed, float *ySpeed, char *estado, controls_t) {
    // Al deshabilitar, inmovilizo a Mario a la pos actual
    *xSpeed = .0f;
    *ySpeed = .0f;

    *estado = DESCONECTADO;
    return instance;
}