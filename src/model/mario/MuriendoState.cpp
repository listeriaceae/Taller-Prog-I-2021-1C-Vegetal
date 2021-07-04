#include "MuriendoState.h"
#include "SueloState.h"
#include "../../utils/Constants.hpp"
#include <iostream>


#define PASAR_A_MURIENDO_ESTADO_2 20
#define PASAR_A_MURIENDO_ESTADO_3 40
#define PASAR_A_ESTADO_SUELO 60

MuriendoState  *MuriendoState ::instance = NULL;

MuriendoState ::MuriendoState () {
}

MuriendoState  *MuriendoState ::getInstance() {
    if (instance == NULL) {
        instance = new MuriendoState ();
    }
    return instance;
}

MarioState *MuriendoState ::update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado, controls_t, char *contador) {
    switch (*estado)
    {
        case MURIENDO_1:
            *contador = *contador + 1;
            if(*contador == PASAR_A_MURIENDO_ESTADO_2)
                *estado = MURIENDO_2;
            break;
        case MURIENDO_2:
            *contador = *contador + 1;
            if(*contador == PASAR_A_MURIENDO_ESTADO_3)
                *estado = MURIENDO_3;
            break;
        case MURIENDO_3:
            *contador = *contador + 1;
            if(*contador == PASAR_A_ESTADO_SUELO){
                *x = MARIO_START_X;
                *y = MARIO_START_Y;
                *xSpeed = 0;
                *ySpeed = 0;
                return SueloState::getInstance();
            }
            break;  
        default:
            *contador = 0;
            *estado = MURIENDO_1;
            break;
    }
    return instance;
}