#include "Mario.hpp"
#include <string>
#include <iostream>
#include "../logger.h"

#define MAX_DESPLAZAMIENTO_X 224
#define MAX_DESPLAZAMIENTO_Y 232
#define MARIO_VEL_X 0.5
#define MARIO_VEL_SALTO 1
#define GRAVEDAD -0.03125

Mario::Mario(float x, float y, SDL_Renderer *renderer)
: Entidad(x, y, ANCHO_MARIO, ALTO_MARIO) {
    this->velX = 0;
    this->velEnSuelo = 0;
    this->velY = 0;
    this->estado = REPOSO;
    this->estadoEnSuelo = REPOSO;
    this->compVista = new ComponenteVistaMario(renderer);
}

void Mario::mover() {
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
        posX -= velX;
        velX -= 2 * velX * (posY < MAX_DESPLAZAMIENTO_Y);
        }
}

void Mario::mostrar() {
    compVista->mostrar(posX, posY, estado);
}

void Mario::setEstado(char up, char down, char left, char right) {
    if (up ^ down) trepar();
    if (left ^ right) correr(right);
    else detener();
}

void Mario::trepar() {}              // TODO

void Mario::correr(char right) {
    this->velEnSuelo = ((- 1) + (right << 1)) * MARIO_VEL_X;
    this->estadoEnSuelo = CORRIENDO;
    if (!this->velY) {                      // TODO: actualizar a si está parado en una plataforma
        this->velX = this->velEnSuelo;
        this->estado = this->estadoEnSuelo;
    }
}

void Mario::detener() {
    this->velEnSuelo = 0;
    this->estadoEnSuelo = REPOSO;
    if (!this->velY) {                      // TODO: actualizar a si está parado en una plataforma
        this->velX = 0;
        this->estado = REPOSO;
    }
}

void Mario::saltar() {
    if (this->velY != 0) return;                 // TODO: actualizar a si está parado en una plataforma
    this->velY = MARIO_VEL_SALTO;
    this->estado = SALTANDO;
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

void Mario::getEstado(float *x, float *y, char *estado) {
    *x = posX;
    *y = posY;
    *estado = this->estado;
}