#include "Mario.hpp"
#include <string>
#include <iostream>
#include "../logger.h"

#define MAX_DESPLAZAMIENTO_X 224
#define MAX_DESPLAZAMIENTO_Y 240
#define MARIO_VELX 2
#define MARIO_VEL_SALTO 4
#define MARIO_ACC -0.2

Mario::Mario(float x, float y)
: Entidad(x, y, MARIO_ANCHO, MARIO_ALTO) {
    this->velX = 0;
    this->velEnSuelo = 0;
    this->velY = 0.;
    this->estado = REPOSO;
    this->sentido = 1;
}

void Mario::mover() {
    posY -= this->velY;
    this->velY += MARIO_ACC * (this->estado == SALTANDO);
    if (posY > MAX_DESPLAZAMIENTO_Y) {
        this->velX = this->velEnSuelo;
        this->estado = this->enstadoEnSuelo;
        this->posY = MAX_DESPLAZAMIENTO_Y;
        this->velY = 0.;
    }
    posX += this->velX;

    if ((posX < 0) || ((posX + MARIO_ANCHO) > MAX_DESPLAZAMIENTO_X)) posX -= velX;
}

void Mario::mostrar(Uint32 frames) {
    compVista->mostrar(frames);
}

void Mario::set_estado(char up, char down, char left, char right) {
    if (up ^ down) trepar(up);
    if (left ^ right) caminar(right);
    else detener();
}

void Mario::trepar(char up) {}              // TODO

void Mario::caminar(char right) {
    this->sentidoEnSuelo = (- 1) + (right << 1);
    this->velEnSuelo = MARIO_VELX * sentidoEnSuelo;
    this->estadoEnSuelo = CORRIENDO;

    if (!this->velY) {                      // TODO: actualizar a si está parado en una plataforma
    this->velX = this->velEnSuelo;
    this->estado = this->estadoEnSuelo;
    this->sentido = right;
    }
}

void Mario::detener() {
    this->velEnSuelo = 0;
    this->enstadoEnSuelo = REPOSO;
    if (!this->velY) {                      // TODO: actualizar a si está parado en una plataforma
    this->velX = 0;
    this->estado = REPOSO;
    }
}

void Mario::saltar() {
    if (this->velY) return;                 // TODO: actualizar a si está parado en una plataforma
    this->velY = MARIO_VEL_SALTO;
    this->estado = SALTANDO;
}

int Mario::getEstado() {
    return this->estado;
}