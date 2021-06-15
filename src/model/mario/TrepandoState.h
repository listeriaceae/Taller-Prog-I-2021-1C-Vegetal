#pragma once
#include "MarioState.h"

class TrepandoState : public MarioState
{
    public:
        MarioState *handleInput(char controls, float *xSpeed, float *ySpeed, char *);
        MarioState *update(float *, float *y, float *xSpeed, float *ySpeed, char *estado);
        static TrepandoState *getInstance();
        void setLadder(Ladder *ladder);

    private:
        TrepandoState();
        static TrepandoState *instance;
        Ladder *ladder;
};