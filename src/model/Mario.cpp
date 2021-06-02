#include "Mario.hpp"
#include "../utils/Constants.hpp"

#define MAX_DESPLAZAMIENTO_X 224
#define MAX_DESPLAZAMIENTO_Y 232
#define MARIO_VEL_X 0.5
#define MARIO_VEL_SALTO 1
#define GRAVEDAD -0.03125

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO) {}

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
        posX -= this->velX;
        this->velX -= 2 * this->velX * (this->estado == SALTANDO);
    }
}

void Mario::setEstado(char controls) {
    trepar();
    correr(controls);
    saltar(controls);
}

void Mario::trepar() {}              // TODO

void Mario::correr(char controls) {
    this->velEnSuelo = (((controls & RIGHT) != 0) - ((controls & LEFT) != 0)) * MARIO_VEL_X;
    this->estadoEnSuelo = REPOSO + (CORRIENDO - REPOSO) * (this->velEnSuelo != 0);
    // TODO: actualizar a si está parado en una plataforma
    if (this->estado != SALTANDO) {
        this->velX = this->velEnSuelo;
        this->estado = this->estadoEnSuelo;
    }
}

void Mario::saltar(char controls) {
    // TODO: actualizar a si está parado en una plataforma
    if (this->estado != SALTANDO && (controls & SPACE)) {
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
    estadoMario.pos.x = posX;
    estadoMario.pos.y = posY;
    estadoMario.estado = this->estado;
    return estadoMario;
}