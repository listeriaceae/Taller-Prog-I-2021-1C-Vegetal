#include "Ladder.h"

Ladder::Ladder(float x, float bottom, float top) {
    this->x = x;
    this->bottom = bottom;
    this->top = top;
}

float Ladder::getX() {
    return this->x;
}

float Ladder::getBottom() {
    return this->bottom;
}

float Ladder::getTop() {
    return this->top;
}