#pragma once

enum {STILL = 0, WALK = 1, JUMP = 14, CLIMB = 3};

class Mario
{
    public:
        float x;
        float y;
        int action;

        Mario();
};