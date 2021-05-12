#ifndef MODEL_MARIO_H
#define MODEL_MARIO_H

enum {STILL = 0, WALK = 1, JUMP = 14, CLIMB = 3};

class Mario
{
    public:
        float x;
        float y;
        int action;

        Mario();
};

#endif