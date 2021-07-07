#pragma once
#include "Entidad.h"
#include "mario/MarioState.h"
#include "../utils/marioStructs.h"

class Mario : public Entidad
{
public:
    Mario();
    void setPos(float x, float y);
    inline void setControls(controls_t controls) { this->controls = controls; }
    void setStage(const Stage *stage) const;
    void mover();
    inline void disable() { isEnabled = false; }
    inline void enable() { isEnabled = true; }
    estadoMario_t getEstado() const;

private:
    MarioState *state;
    bool isEnabled = true;
    controls_t controls = {0, 0, 0, 0, 0};
    char estado;
    float velX;
    float velY;
};