#pragma once
#include "MarioState.h"

class SueloState : public MarioState
{
    public:
        MarioState *handleInput(char controls, float *xSpeed, float *ySpeed, char *estado);
        MarioState *update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado);
        static SueloState *getInstance();
    
    private:
        SueloState();
        static SueloState *instance;
};