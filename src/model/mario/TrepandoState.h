#pragma once
#include "MarioState.h"

class TrepandoState : public MarioState
{
public:
    MarioState *update(float &, float &y, float &, float &ySpeed, char &estado, controls_t controls);
    static TrepandoState *getInstance();
    void setLimits(float min, float max);

private:
    TrepandoState();
    static TrepandoState *instance;
    float min, max;
};