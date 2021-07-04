#pragma once
#include "MarioState.h"

class SueloState : public MarioState
{
public:
    MarioState *update(Mario *mario);
    static SueloState *getInstance();

private:
    SueloState();
    static SueloState *instance;
};