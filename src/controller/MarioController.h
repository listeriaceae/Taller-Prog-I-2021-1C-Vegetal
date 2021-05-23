#pragma once
#include "../model/Mario.hpp"

class MarioController {
    public:
        MarioController(Mario *mario);
        void handleEvent(SDL_Event *e);
    private:
        Mario *mario;
        char up = 0;
        char down = 0;
        char left = 0;
        char right = 0;
};