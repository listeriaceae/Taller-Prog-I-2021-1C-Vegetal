#include "MuriendoState.h"
#include "SueloState.h"
#include "../../utils/Constants.hpp"
#include <iostream>

MuriendoState  *MuriendoState ::instance = NULL;

MuriendoState ::MuriendoState () {
}

MuriendoState  *MuriendoState ::getInstance() {
    if (instance == NULL) {
        instance = new MuriendoState ();
    }
    return instance;
}

MarioState *MuriendoState ::update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado, controls_t) {
    switch (*estado)
    {
        case MURIENDO_1:
            this->contador++;
            if(this->contador == 20)
                *estado = MURIENDO_2;
            break;
        case MURIENDO_2:
            this->contador++;
            if(this->contador == 40)
                *estado = MURIENDO_3;
            break;
        case MURIENDO_3:
            this->contador++;
            if(this->contador == 60){
                *x = MARIO_START_X;
                *y = MARIO_START_Y;
                *xSpeed = 0;
                *ySpeed = 0;
                return SueloState::getInstance();
            }
            break;  
        default:
            this->contador = 0;
            *estado = MURIENDO_1;
            break;
    }
    return instance;
}