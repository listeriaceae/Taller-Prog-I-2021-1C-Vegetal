#pragma once
#include "Entidad.h"
#include "mario/MarioState.h"
#include "../utils/estadoMario.h"

class Mario : public Entidad 
{
    public: 
        Mario();
        void setPos(float x, float y);
        void setEstado(char controls);
        void setStage(Stage *stage);
        void mover();
        estadoMario_t getEstado();

    private:
        MarioState *state;
};