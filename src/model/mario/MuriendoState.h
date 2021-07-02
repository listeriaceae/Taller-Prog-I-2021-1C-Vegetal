#pragma once
#include "MarioState.h"

class MuriendoState  : public MarioState
{
    public:
        MarioState *update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado, controls_t);
        static MuriendoState  *getInstance();

    private:
        MuriendoState ();
        unsigned int contador;
        static MuriendoState  *instance;
};