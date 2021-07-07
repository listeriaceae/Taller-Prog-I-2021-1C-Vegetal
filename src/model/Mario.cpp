#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.h"
#include "mario/MuriendoState.h"

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO) {
    this->state = SueloState::getInstance();
}

void Mario::setPos(const float x, const float y) {
    if (lives == 0) return;
    this->pos.x = x;
    this->pos.y = y;
    this->state = SueloState::getInstance();
}

void Mario::setStage(const Stage *stage) const {
    MarioState::setStage(stage);
}

void Mario::mover() {
    this->state = this->state->update(*this);
}

const MarioState *Mario::die() {
    lives -= (contador == 0);
    return MuriendoState::getInstance();
}

estadoMario_t Mario::getEstado() const {
    estadoMario_t estadoMario;
    estadoMario.pos = pos;
    estadoMario.estado = this->estado;
    estadoMario.isEnabled = isEnabled;
    return estadoMario;
}