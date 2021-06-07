#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/ReposoState.h"

#include <stdio.h>
#include <iostream>

#define MAX_DESPLAZAMIENTO_X 224
#define MAX_DESPLAZAMIENTO_Y 232
#define MARIO_VEL_X 0.5
#define MARIO_VEL_SALTO 1
#define GRAVEDAD -0.03125

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO) {
    this->state = ReposoState::getInstance();
    std::cout << "Estado inicial " << this->state->getName() << std::endl;
}

void Mario::mover() {
    this->state->update();

    posY -= this->velY;
    this->velY += GRAVEDAD * (this->estado == SALTANDO);
    if (posY > MAX_DESPLAZAMIENTO_Y) {
        this->velX = this->velEnSuelo;
        this->estado = this->estadoEnSuelo;
        this->posY = MAX_DESPLAZAMIENTO_Y;
        this->velY = 0.;
    }
    posX += this->velX;

    if ((posX < 0) || ((posX + ANCHO_MARIO) > MAX_DESPLAZAMIENTO_X)) {
        posX -= this->velX;
        this->velX -= 2 * this->velX * (this->estado == SALTANDO);
    }
}

void Mario::setEstado(char controls) {
    this->state = this->state->handleInput(controls, this);
    this->state->perform();
    std::cout << "ESTADO -> " << this->state->getName() << std::endl;

    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    correr(left, right);

    char space = controls & SPACE;
    saltar(space);
}

// void Mario::trepar(char up, char down) {} TODO

void Mario::correr(char left, char right) {
    this->velEnSuelo = (right - left) * MARIO_VEL_X;
    this->estadoEnSuelo = REPOSO + (CORRIENDO - REPOSO) * (this->velEnSuelo != 0);

    // TODO: actualizar a si está parado en una plataforma
    if (this->estado != SALTANDO) {
        this->velX = this->velEnSuelo;
        this->estado = this->estadoEnSuelo;
    }
}

void Mario::saltar(char space) {
    // TODO: actualizar a si está parado en una plataforma
    if (this->estado != SALTANDO && space) {
        this->velY = MARIO_VEL_SALTO;
        this->estado = SALTANDO;
    }
}

void Mario::setStartPos(float x, float y) {
    posX = x;
    posY = y;
    this->velX = 0;
    this->velEnSuelo = 0;
    this->velY = 0;
    this->estado = REPOSO;
    this->estadoEnSuelo = REPOSO;
}

estadoMario_t Mario::getEstado() {
    estadoMario_t estadoMario;
    estadoMario.pos = getPos();
    estadoMario.estado = this->estado;
    return estadoMario;
}