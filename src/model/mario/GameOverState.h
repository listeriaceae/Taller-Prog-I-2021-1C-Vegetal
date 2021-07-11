#pragma once
#include "MarioState.h"

class GameOverState : public MarioState
{
public:
    const MarioState *update(Mario &mario) const;
    const MarioState *reset(float, float, Mario &) const;
    static const GameOverState *getInstance();

private:
    GameOverState() = default;
    ~GameOverState() = default;
    static const GameOverState instance;
};