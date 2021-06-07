#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class CorriendoLeftState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        static CorriendoLeftState* getInstance();
    
    private:
        CorriendoLeftState();
        static CorriendoLeftState* instance;
        float velX;
};