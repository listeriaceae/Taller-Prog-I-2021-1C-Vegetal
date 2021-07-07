#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.h"

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO) {
    this->state = SueloState::getInstance();
}

void Mario::setPos(const float x, const float y) {
    this->pos.x = x;
    this->pos.y = y;
    this->state = SueloState::getInstance();
}

void Mario::setStage(const Stage *stage) const {
    this->state->setStage(stage);
}

void Mario::mover() {
    this->state = this->state->update(pos.x, pos.y, velX, velY, estado, controls);
}

estadoMario_t Mario::getEstado() const {
    estadoMario_t estadoMario;
    estadoMario.pos = pos;
    if(this->isEnabled) {
        estadoMario.estado = this->estado;
    } else {
        estadoMario.estado = DESCONECTADO;
    }
    return estadoMario;
}