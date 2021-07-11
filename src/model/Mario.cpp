#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.h"
#include "mario/MuriendoState.h"

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO), state(SueloState::getInstance()) {}

void Mario::reset(const float x, const float y) {
    this->state = this->state->reset(x, y, *this);
}

void Mario::setStage(const Stage *stage) const {
    MarioState::setStage(stage);
}

void Mario::mover() {
    this->state = this->state->update(*this);
    controls.space = 0;
}

void Mario::die() {
    if (contador != 0) return;
    ++contador;
    --lives;
    this->state = MuriendoState::getInstance();
}

estadoMario_t Mario::getEstado() const {
    return {pos, estado, isEnabled, lives};
}