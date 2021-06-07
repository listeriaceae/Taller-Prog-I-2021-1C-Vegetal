#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class SaltandoState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        static SaltandoState* getInstance();
    
    private:
        SaltandoState();
        static SaltandoState* instance;
};