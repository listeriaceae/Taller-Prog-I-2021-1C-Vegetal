#pragma once
#include "MarioState.h"

class DisabledState : public MarioState
{
    public:
        MarioState *update(float *x, float *y, float *xSpeed, float *ySpeed, char *estado, controls_t);
        static DisabledState *getInstance();

    private:
        DisabledState();
        static DisabledState *instance;
};