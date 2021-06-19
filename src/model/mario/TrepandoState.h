#pragma once
#include "MarioState.h"

class TrepandoState : public MarioState
{
    public:
        MarioState *handleInput(controls_t controls, float *xSpeed, float *ySpeed);
        MarioState *update(float *, float *y, float *xSpeed, float *ySpeed, char *estado);
        static TrepandoState *getInstance();
        void setLadder(Ladder *ladder);

    private:
        TrepandoState();
        static TrepandoState *instance;
        Ladder *ladder;
};