#pragma once
#include "../model/Mario.hpp"

class MarioController {
    public:
        MarioController(Mario *mario);
        void handleEvent(SDL_Event *e);
    private:
        Mario *mario;
        char up;
        char down;
        char left;
        char right;
};