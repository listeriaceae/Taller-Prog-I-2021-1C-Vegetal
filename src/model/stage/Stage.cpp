#include "Stage.h"
#include <cmath>

void Stage::addLadder(Ladder *ladder) {
    ladders.push_back(ladder);
}

Ladder *Stage::getLadder(float x, float y) {
    for (Ladder *ladder : ladders) {
        if (std::abs(ladder->getX() - x) < 2 &&
        (std::abs(ladder->getBottom() - y) < 1 ||
        std::abs(ladder->getTop() - y) < 1))
        {
            return ladder;
        }
    }
    return NULL;
}

MarioState *Stage::collide(float *x, float *y, float *dx, float *dy) {
    for (Platform *platform : platforms) {
        
    }
    for (MovingPlatform *platform : movingPlatforms) {
        
    }
}