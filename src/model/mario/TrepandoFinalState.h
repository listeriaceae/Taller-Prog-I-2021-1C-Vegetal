#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class TrepandoFinalState : public MarioState
{
    public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        virtual char getEstado();
        static TrepandoFinalState* getInstance();
    
    private:
        TrepandoFinalState();
        static TrepandoFinalState* instance;
};