#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class ReposoState : public MarioState
{
    public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        virtual char getEstado();
        static ReposoState* getInstance();
    
    private:
        ReposoState();
        static ReposoState* instance;
};