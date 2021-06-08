#pragma once

#include "../Mario.hpp"
#include "MarioState.h"

class TrepandoReposoState : public MarioState
{
     public:
        virtual MarioState* handleInput(char controls, Mario* mario);
        virtual void update();
        virtual void perform();
        virtual char getEstado();
        static TrepandoReposoState* getInstance();
        void setDir(char up, char down);
        void setEscalera(Escalera* e);

    private:
        TrepandoReposoState();
        static TrepandoReposoState* instance;
        char up;
        char down;
        Escalera* e;
        char estado;
};