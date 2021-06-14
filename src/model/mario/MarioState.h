#pragma once
#include "../stage/Stage.h"

#define SPACE 128
#define UP 8
#define DOWN 4
#define LEFT 2
#define RIGHT 1

#define MARIO_VEL_X 0.5f
#define MARIO_VEL_SALTO 1.f
#define MARIO_VEL_TREPAR 0.5f

class MarioState {
    public:
        void setStage(Stage *stage);
        virtual MarioState* handleInput(char controls) = 0;
        virtual MarioState* update(float *x, float *y) = 0;
        char getEstado();
        virtual ~MarioState() = default;

    protected:
        MarioState();
        static Stage *stage;
        static char estado;
        static float velX;
        static float velY;
};