#pragma once
#include <list>
#include <vector>
#include "Ladder.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "../mario/SueloState.h"
#include "../mario/AireState.h"

class Stage {
    public:
        void addLadder(Ladder *ladder);
        Ladder *getLadder(float x, float y);
        void addPlatform(Platform *platform);
        std::vector<Platform *> *getPlatforms();
        void addMovingPlatform(MovingPlatform *platform);
        MarioState *Stage::collide(float *x, float *y, float *dx, float *dy);
        ~Stage();

    private:
        std::list<Ladder *> ladders;
        std::vector<Platform *> platforms;
        std::list<MovingPlatform *> movingPlatforms;
};