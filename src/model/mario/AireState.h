#pragma once
#include "MarioState.h"

class AireState : public MarioState
{
    public:
        MarioState *handleInput(char, float *, float *, char *);
        MarioState *update(float *x, float *y, float *xSpeed, float *ySpeed, char *);
        static AireState *getInstance();

    private:
        AireState();
        static AireState *instance;
};