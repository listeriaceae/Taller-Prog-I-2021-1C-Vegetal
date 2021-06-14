#pragma once
#include "Tile.h"
#include "Ladder.h"
#include "Platform.h"
#include "../../utils/Constants.hpp"

class Stage {
    public:
        Stage();
        void addLadder(Ladder *ladder);
        Ladder *getLadder(float x, float y, float ySpeed);
        void addPlatform(Platform *platform);
        bool collide(float *x, float *y, float *dx, float *dy);
        ~Stage();

    private:
        Tile *grid[(ANCHO_NIVEL / ANCHO_TILE + 1) * (ALTO_NIVEL / ALTO_TILE + 1)];
};