#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class SaltandoState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        virtual char getEstado();
        static SaltandoState* getInstance();
        void setDir(char left, char right, float velX);
    
    private:
        SaltandoState();
        static SaltandoState* instance;
        char left;
        char right;
};