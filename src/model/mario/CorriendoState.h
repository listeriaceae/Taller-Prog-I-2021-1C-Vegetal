#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class CorriendoState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        static CorriendoState* getInstance();
    
    private:
        CorriendoState();
        static CorriendoState* instance;
};