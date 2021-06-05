#pragma once
#include "../model/Mario.hpp"

class MarioController {
    public:
        MarioController(Mario *mario);
        void update();
    private:
        Mario *mario;
};