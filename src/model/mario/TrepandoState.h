#pragma once
#include "MarioState.h"

class TrepandoState : public MarioState
{
public:
    MarioState *update(float *, float *y, float *xSpeed, float *ySpeed, char *estado, controls_t controls, char *);
    static TrepandoState *getInstance();
    void setLadder(Ladder *ladder);

private:
    TrepandoState();
    static TrepandoState *instance;
    Ladder *ladder;
};