#include "SueloState.h"
#include "TrepandoState.h"
#include "../../utils/Constants.hpp"

TrepandoState *TrepandoState::instance{nullptr};

TrepandoState::TrepandoState() {}

TrepandoState *TrepandoState::getInstance() {
    if (instance == nullptr) {
        instance = new TrepandoState();
    }
    return instance;
}

void TrepandoState::setLimits(const float min, const float max) {
    this->min = min;
    this->max = max;
}

MarioState *TrepandoState::update(float &, float &y, float &, float &ySpeed, char &estado, const controls_t controls) {
    ySpeed = (controls.up - controls.down) * MARIO_VEL_TREPAR;
    if ((ySpeed <= 0 && std::abs(min - y) <= MARIO_VEL_TREPAR / 2)
    || (ySpeed >= 0 && std::abs(max - y) <= MARIO_VEL_TREPAR / 2))
    {
        estado = DE_ESPALDAS;
        return SueloState::getInstance();
    }
    y -= ySpeed;
    estado = TREPANDO;
    return instance;
}