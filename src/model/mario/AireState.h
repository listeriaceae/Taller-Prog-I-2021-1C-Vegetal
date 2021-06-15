#pragma once
#include "MarioState.h"

class AireState : public MarioState
{
    public:
        MarioState *handleInput(char, float *, float *);
        MarioState *update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado);
        static AireState *getInstance();

    private:
        AireState();
        static AireState *instance;
};