#include "Mario.hpp"
#include <string>
#include <iostream>
#include "../logger.h"
#include <stdio.h>
#include <iostream>

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
    float auxY = posY;
    posY -= this->velY;
    this->velY += GRAVEDAD * (this->estado == SALTANDO);

    char auxEstado = this->estado;

    if (posY > MAX_DESPLAZAMIENTO_Y) {
        this->velX = this->velEnSuelo;
        this->estado = this->estadoEnSuelo;
        this->posY = MAX_DESPLAZAMIENTO_Y;
        this->velY = 0.;

        if( this->escalera()
            && auxEstado == TREPANDO
            && auxEstado == TREPANDO_REPOSO) {
                this->estado = TREPANDO_REPOSO;
        }
    }
    posX += this->velX;

    if ((posX < 0) || ((posX + ANCHO_MARIO) > MAX_DESPLAZAMIENTO_X)) {
        posX -= velX;
        velX -= 2 * velX * (posY < MAX_DESPLAZAMIENTO_Y);
    }

    // Nivel 1
    if (this->posY < 184) {
        this->posY = auxY;
        this->velY = 0.;
    }
}

void Mario::mostrar() {
    compVista->mostrar(posX, posY, estado);
}

void Mario::setEstado(char up, char down, char left, char right) {
    if (up ^ down) {
         trepar(up, down);
    } else {
        if (this->escalera())
            detenerTrepar();
    }

    if (left ^ right) {
         correr(right);
    } else {
         detener();
    }
}

void Mario::trepar(char up, char down) {
    if (!(this->posX >= 24 && this->posX <= 32)) {
        std::cout << "NO ESTA EN LA ESCALERA " << this->posX << "," << this->posY << std::endl;
        return;
    }

    // mientras subo la escalera
    // fijo el x en 28 y la velocidad en x en 0
    this->posX = 28;
    this->velX = 0;

    char isUp = (up == 1) ? 'Y' : 'N';
    
    if (isUp == 'Y') {
        this->velY = MARIO_VEL_X;
        std::cout << "UP " << this->posX << "," << this->posY << std::endl;
        this->estado = TREPANDO;
    } else {
        std::cout << "DOWN " << this->posX << "," << this->posY << std::endl;
        this->estado = TREPANDO;
        this->velX = 0;
        this->velY = -MARIO_VEL_X;
    }
}

void Mario::detenerTrepar() {
    this->velX = 0;
    this->velY = 0;
    this->estado = TREPANDO_REPOSO;
}

bool Mario::escalera() {
    // En escaleras
    // no permito despalzaientos en X
    // 1) escaera entre y == 232 y == 188
    if (this->posY <= MAX_DESPLAZAMIENTO_Y
        && this->posY > 188
        && this->posX == 28
        && this->velX == 0) {
            std::cout << "ESCALERA " << this->posX << "," << this->posY << std::endl;
            return true;
    } else {
        return false;
    }
}

void Mario::correr(char right) {
    if (this->escalera()) return;

    this->velEnSuelo = ((- 1) + (right << 1)) * MARIO_VEL_X;
    this->estadoEnSuelo = CORRIENDO;
    if (this->velY == 0) {                      // TODO: actualizar a si está parado en una plataforma
        this->velX = this->velEnSuelo;
        this->estado = this->estadoEnSuelo;
    }
}

void Mario::detener() {
    this->velEnSuelo = 0;
    this->estadoEnSuelo = REPOSO;
    if (this->velY == 0 && this->posY == MAX_DESPLAZAMIENTO_Y) {                      // TODO: actualizar a si está parado en una plataforma
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