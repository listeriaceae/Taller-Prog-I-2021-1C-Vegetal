#include "MovingPlatform.h"
#include "../../utils/Constants.hpp"

#define MIN_X 17
#define MAX_X 191
#define MIN_Y_PLATFORM 124

#define X_PLAT_INDEX 58
#define Y_PLAT_INDEX 40
#define MAX_PLATFORMS 3
#define PLATFORM_SPEED 0.25

MovingPlatform::MovingPlatform(int platform, int level)
: Platform(0, 0, 0, 0) {
    this->direction = (((level + 1) & 2) - 1);
    int limit = ((MAX_X + MIN_X) / 2) + direction * ((MAX_X - MIN_X) / 2);

    start.x = limit - direction * platform * X_PLAT_INDEX;
    start.y = MIN_Y_PLATFORM + (level / 2) * Y_PLAT_INDEX + (level % 2) * ALTO_PLATAFORMA;
    end.x = start.x + ANCHO_PLATAFORMA;
    end.y = start.y;
}

void MovingPlatform::getLimits(float *min, float *max) {
    *min = MIN_X;
    *max = MAX_X + ANCHO_PLATAFORMA;
}

float MovingPlatform::getSpeed() {
    return this->direction * PLATFORM_SPEED;
}

void MovingPlatform::move() {
    start.x += this->direction * PLATFORM_SPEED;
    start.x -= this->direction * (MAX_PLATFORMS * X_PLAT_INDEX) * ((start.x < MIN_X) || (MAX_X < start.x));
    end.x = start.x + ANCHO_PLATAFORMA;
}

punto_t MovingPlatform::getPos() {
    return start;
}