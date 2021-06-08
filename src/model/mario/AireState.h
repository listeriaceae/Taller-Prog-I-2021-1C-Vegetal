#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class AireState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        virtual char getEstado();
        static AireState* getInstance();
        void setDir(char left, char right, float velY, float velX);
    
    private:
        AireState();
        static AireState* instance;
        char left;
        char right;
};