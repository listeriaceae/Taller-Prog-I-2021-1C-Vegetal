#pragma once
#include "MarioState.h"

class GameOverState : public MarioState
{
public:
    MarioState *update(Mario *mario);
    static GameOverState *getInstance();

private:
    GameOverState();
    static GameOverState *instance;
};