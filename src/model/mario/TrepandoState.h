#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class TrepandoState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        virtual char getEstado();
        static TrepandoState* getInstance();
        void setDir(char up, char down);
        void setEscalera(Escalera* e);

    private:
        TrepandoState();
        void clear();
        static TrepandoState* instance;
        char up;
        char down;
        Escalera* e;
        char estado;
};