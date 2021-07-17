#pragma once
#include "Entidad.h"
#include "../utils/Constants.hpp"


class Barril : public Entidad
{
public:
    Barril(float x, float y);
    void mover();
    bool estaEnNivel() const { return pos.y < ALTO_NIVEL; }
    dimensiones_t dimensions() const;
    void destroy();
private:
    float velX;
    float velY;
    bool isBroken = false;
};