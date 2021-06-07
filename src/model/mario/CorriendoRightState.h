#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class CorriendoRightState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        static CorriendoRightState* getInstance();
    
    private:
        CorriendoRightState();
        static CorriendoRightState* instance;
};