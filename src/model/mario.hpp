#pragma once

enum {STILL = 0, WALKING = 1, JUMPING = 14, CLIMBING = 3};

class Mario
{
    public:
        float x;
        float y;
        int action;

        Mario();
};