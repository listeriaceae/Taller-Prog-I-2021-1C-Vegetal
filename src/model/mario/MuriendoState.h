#pragma once
#include "MarioState.h"

class MuriendoState  : public MarioState
{
    public:
        MarioState *update(Mario *mario);
        static MuriendoState  *getInstance();

    private:
        MuriendoState ();
        static MuriendoState  *instance;
};