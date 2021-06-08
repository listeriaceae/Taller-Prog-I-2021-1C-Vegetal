#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/ReposoState.h"

#include <stdio.h>
#include <iostream>

#define MAX_DESPLAZAMIENTO_X 228
#define MAX_DESPLAZAMIENTO_Y 232

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO) {
    this->state = ReposoState::getInstance();
    std::cout << "Estado inicial " << this->state->getName() << std::endl;
}

void Mario::mover() {
    this->state->update();
    float velY = this->state->getVelY();
    float velX = this->state->getVelX();

    posY -= velY;

    posX += velX;

    if ((posX < -4) || ((posX + ANCHO_MARIO) > MAX_DESPLAZAMIENTO_X)) {
        posX -= velX;
    }
}

void Mario::setEstado(char controls) {
    this->state = this->state->handleInput(controls, this);
    this->state->perform();
    std::cout << "ESTADO -> " << this->state->getName() << std::endl;
}

void Mario::setPos(float x, float y) {
    this->posX = x;
    this->posY = y;
}

estadoMario_t Mario::getEstado() {
    estadoMario_t estadoMario;
    estadoMario.pos = getPos();
    estadoMario.estado = this->state->getEstado();
    return estadoMario;
}