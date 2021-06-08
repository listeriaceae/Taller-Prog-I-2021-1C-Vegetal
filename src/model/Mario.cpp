#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/ReposoState.h"

#include <stdio.h>
#include <iostream>

#define MAX_DESPLAZAMIENTO_X 224
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

    if ((posX < 0) || ((posX + ANCHO_MARIO) > MAX_DESPLAZAMIENTO_X)) {
        posX -= velX;
        // velX -= 2 *velX * (this->estado == SALTANDO);
    }
}

void Mario::setEstado(char controls) {
    this->state = this->state->handleInput(controls, this);
    this->state->perform();
    std::cout << "ESTADO -> " << this->state->getName() << std::endl;
}

void Mario::setStartPos(float x, float y) {
    posX = x;
    posY = y;
    this->state = ReposoState::getInstance();
}

estadoMario_t Mario::getEstado() {
    estadoMario_t estadoMario;
    estadoMario.pos = getPos();
    estadoMario.estado = this->state->getEstado();
    return estadoMario;
}