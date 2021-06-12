#pragma once
#include "../../utils/punto.h"

class Platform {
    public:
        Platform(float x1, float y1, float x2, float y2);
        punto_t getRandomPoint(int entityWidth);
        void getLimits(float *min, float *max);
        virtual ~Platform() = default;

    protected:
        punto_t start;
        punto_t end;
};