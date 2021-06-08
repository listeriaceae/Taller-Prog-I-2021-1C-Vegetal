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
        void setDir(char left, char right);
    
    private:
        CorriendoState();
        static CorriendoState* instance;
        char left;
        char right;
};