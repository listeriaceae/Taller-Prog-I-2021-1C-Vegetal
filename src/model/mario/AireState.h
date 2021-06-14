#pragma once
#include "MarioState.h"

class AireState : public MarioState
{
    public:
        MarioState *handleInput(char);
        MarioState *update(float *x, float *y);
        static AireState *getInstance();

    private:
        AireState();
        static AireState *instance;
};