#pragma once

#include "Entidad.h"
#include "../utils/estadoMario.h"
#include "mario/MarioState.h"

class Mario : public Entidad 
{
    public: 
        Mario();
        void setPos(float x, float y);
        void mover();
        void setEstado(char controls);
        estadoMario_t getEstado();

    private:
        MarioState* state;
};