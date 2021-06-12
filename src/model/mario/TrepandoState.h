#pragma once

#include "MarioState.h"

class TrepandoState : public MarioState
{
    public:
        MarioState* handleInput(char controls);
        MarioState* update(float *x, float *y);
        static TrepandoState* getInstance();
        void setLadder(Ladder *ladder);

    private:
        TrepandoState();
        static TrepandoState* instance;
        Ladder *ladder;
};