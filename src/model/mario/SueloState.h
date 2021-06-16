#pragma once
#include "MarioState.h"

class SueloState : public MarioState
{
    public:
        MarioState *handleInput(controls_t controls, float *xSpeed, float *ySpeed);
        MarioState *update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado);
        static SueloState *getInstance();
    
    private:
        SueloState();
        static SueloState *instance;
};