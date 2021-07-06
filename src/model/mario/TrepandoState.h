#pragma once
#include "MarioState.h"

class TrepandoState : public MarioState
{
public:
    MarioState *update(Mario *mario);
    static TrepandoState *getInstance();
    void setLadder(Ladder *ladder);

private:
    TrepandoState();
    static TrepandoState *instance;
    Ladder *ladder;
};