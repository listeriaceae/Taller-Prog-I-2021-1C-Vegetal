#pragma once
#include "../model/Mario.hpp"

class MarioController {
    public:
        MarioController();
        void update();
        controls_t getControls();
    private:
};