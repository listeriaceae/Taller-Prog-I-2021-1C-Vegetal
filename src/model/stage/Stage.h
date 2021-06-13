#pragma once
#include <list>
#include <vector>
#include "Tile.h"
#include "Ladder.h"
#include "MovingPlatform.h"
#include "../../utils/Constants.hpp"

class Stage {
    public:
        void addLadder(Ladder *ladder);
        Ladder *getLadder(float x, float y, float ySpeed);
        void addPlatform(Platform *platform);
        std::vector<Platform *> *getPlatforms();
        void addMovingPlatform(MovingPlatform *platform);
        bool Stage::collide(float *x, float *y, float *dx, float *dy);
        ~Stage();

    private:
        Tile *grid[(ANCHO_NIVEL / ANCHO_TILE + 1) * (ALTO_NIVEL / ALTO_TILE + 1)];
};