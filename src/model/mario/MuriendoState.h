#pragma once
#include "MarioState.h"

class MuriendoState  : public MarioState
{
    public:
        MarioState *update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado, controls_t, char *contador);
        static MuriendoState  *getInstance();

    private:
        MuriendoState ();
        static MuriendoState  *instance;
};