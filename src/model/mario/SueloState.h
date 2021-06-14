#pragma once
#include "MarioState.h"

class SueloState : public MarioState
{
    public:
        MarioState *handleInput(char controls);
        MarioState *update(float *x, float *y);
        static SueloState *getInstance();
    
    private:
        SueloState();
        static SueloState *instance;
};