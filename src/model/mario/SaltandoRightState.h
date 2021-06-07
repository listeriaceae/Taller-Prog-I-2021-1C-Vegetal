#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class SaltandoRightState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        static SaltandoRightState* getInstance();
    
    private:
        SaltandoRightState();
        static SaltandoRightState* instance;
};