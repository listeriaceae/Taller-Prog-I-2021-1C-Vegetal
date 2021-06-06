#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class ReposoState : public MarioState
{
    public:
        ReposoState();
        virtual void handleInput(char controls);
        virtual void update();
};