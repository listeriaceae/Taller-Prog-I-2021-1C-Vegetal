#pragma once
#include "Entidad.h"
#include "mario/MarioState.h"
#include "../utils/marioStructs.h"

class Mario : public Entidad 
{
    public: 
        Mario();
        void setPos(float x, float y);
        void setEstado(controls_t controls);
        void setStage(Stage *stage);
        void mover();
        estadoMario_t getEstado();

    private:
        MarioState *state;
        char estado;
        float velX;
        float velY;
};