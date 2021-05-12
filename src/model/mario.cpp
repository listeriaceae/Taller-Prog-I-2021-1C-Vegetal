#include "mario.h"

#define INIT_X 10
#define INIT_Y 240

Mario::Mario() {
    x = INIT_X;
    y = INIT_Y;
    action = STILL;
}