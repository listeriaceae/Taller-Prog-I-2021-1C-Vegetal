#pragma once

#include "Platform.h"

class MovingPlatform : public Platform {
    public:
        MovingPlatform(int platform, int level);
        void move();
        punto_t getPos();

    private:
        int direction;
};