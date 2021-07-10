#pragma once

#include "../stage/Stage.h"
#include "../../utils/marioStructs.h"
#include "../Mario.hpp"

#define MARIO_VEL_X 0.5f
#define MARIO_VEL_TREPAR 0.5f
#define MARIO_VEL_SALTO 2.f
#define GRAVEDAD (-(MARIO_VEL_SALTO / 16))

class Mario;

class MarioState
{
public:
    static void setStage(const Stage *stage);
    virtual const MarioState *update(Mario &mario) const = 0;
    virtual const MarioState *resetPos(float x, float y, Mario &mario) const;
    virtual ~MarioState() = default;

protected:
    MarioState() = default;
    static const Stage *stage;
};