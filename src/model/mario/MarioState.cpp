#include "MarioState.h"
#include <string>

const int ESCALERA_1_X0 = 24;
const int ESCALERA_1_X1 = 32;
const int ESCALERA_1_Y0 = 232;
const int ESCALERA_1_Y1 = 184;

const int ESCALERA_2_X0 = 208;
const int ESCALERA_2_X1 = 216;
const int ESCALERA_2_Y0 = 184;
const int ESCALERA_2_Y1 = 144;

const int ESCALERA_3_X0 = -8;
const int ESCALERA_3_X1 = 0;
const int ESCALERA_3_Y0 = 144;
const int ESCALERA_3_Y1 = 104;

const int ESCALERA_4_X0 = 208;
const int ESCALERA_4_X1 = 216;
const int ESCALERA_4_Y0 = 104;
const int ESCALERA_4_Y1 = 72;

const int ESCALERA_5_X0 = 120;
const int ESCALERA_5_X1 = 128;
const int ESCALERA_5_Y0 = 72;
const int ESCALERA_5_Y1 = 40;

MarioState::MarioState() {
    this->velX = 0.;
    this->velY = 0.;

    this->inicializarEscaleras();
}

void MarioState::inicializarEscaleras() {
    Escalera * e1 = new Escalera("E1",
                                ESCALERA_1_X1 -4,
                                ESCALERA_1_X0,
                                ESCALERA_1_X1,
                                ESCALERA_1_Y0,
                                ESCALERA_1_Y1);
    Escalera * e2 = new Escalera("E2",
                                ESCALERA_2_X1 -4,
                                ESCALERA_2_X0,
                                ESCALERA_2_X1,
                                ESCALERA_2_Y0,
                                ESCALERA_2_Y1);
    Escalera * e3 = new Escalera("E3",
                                ESCALERA_3_X1 -4,
                                ESCALERA_3_X0,
                                ESCALERA_3_X1,
                                ESCALERA_3_Y0,
                                ESCALERA_3_Y1);
    Escalera * e4 = new Escalera("E4",
                                ESCALERA_4_X1 -4,
                                ESCALERA_4_X0,
                                ESCALERA_4_X1,
                                ESCALERA_4_Y0,
                                ESCALERA_4_Y1);
    Escalera * e5 = new Escalera("E5",
                                ESCALERA_5_X1 -4,
                                ESCALERA_5_X0,
                                ESCALERA_5_X1,
                                ESCALERA_5_Y0,
                                ESCALERA_5_Y1);
    
    this->escaleras[0] = e1;
    this->escaleras[1] = e2;
    this->escaleras[2] = e3;
    this->escaleras[3] = e4;
    this->escaleras[4] = e5;
}

Escalera* MarioState::getEscalera(punto_t p) {
    if (p.x >= ESCALERA_1_X0 
        && p.x <= ESCALERA_1_X1 
        && p.y <= ESCALERA_1_Y0
        && p.y >= ESCALERA_1_Y1) {
            return this->escaleras[0];
    } else if (p.x >= ESCALERA_2_X0 
        && p.x <= ESCALERA_2_X1 
        && p.y <= ESCALERA_2_Y0
        && p.y >= ESCALERA_2_Y1) {
            return this->escaleras[1];
    } else if (p.x >= ESCALERA_3_X0 
        && p.x <= ESCALERA_3_X1 
        && p.y <= ESCALERA_3_Y0
        && p.y >= ESCALERA_3_Y1) {
            return this->escaleras[2];
    } else if (p.x >= ESCALERA_4_X0 
        && p.x <= ESCALERA_4_X1 
        && p.y <= ESCALERA_4_Y0
        && p.y >= ESCALERA_4_Y1) {
            return this->escaleras[3];
    } else if (p.x >= ESCALERA_5_X0 
        && p.x <= ESCALERA_5_X1 
        && p.y <= ESCALERA_5_Y0
        && p.y >= ESCALERA_5_Y1) {
            return this->escaleras[4];
    }
    return NULL;
}

std::string MarioState::getName() {
    return this->name;
}

float MarioState::getVelY() {
    return this->velY;
}

float MarioState::getVelX() {
    return this->velX;
}