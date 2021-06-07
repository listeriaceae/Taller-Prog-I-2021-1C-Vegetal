#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class SaltandoLeftState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        static SaltandoLeftState* getInstance();
    
    private:
        SaltandoLeftState();
        static SaltandoLeftState* instance;
};