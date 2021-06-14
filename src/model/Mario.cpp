#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.h"

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO) {
    this->state = SueloState::getInstance();
}

void Mario::setEstado(char controls) {
    this->state = this->state->handleInput(controls);
}

void Mario::setPos(float x, float y) {
    this->posX = x;
    this->posY = y;
}

void Mario::setStage(Stage *stage) {
    this->state->setStage(stage);
    this->state = SueloState::getInstance();
}

void Mario::mover() {
    this->state = this->state->update(&posX, &posY);
}

estadoMario_t Mario::getEstado() {
    estadoMario_t estadoMario;
    estadoMario.pos = getPos();
    estadoMario.estado = this->state->getEstado();
    return estadoMario;
}