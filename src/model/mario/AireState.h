#pragma once
#include "MarioState.h"

class AireState : public MarioState
{
public:
    MarioState *update(Mario *mario);
    static AireState *getInstance();

private:
    AireState();
    static AireState *instance;
};