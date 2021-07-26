#pragma once

#include "Entidad.h"
#include "../utils/punto.h"
#include "../utils/dimensiones.h"

class Enemy : public Entidad
{
public:
    Enemy(float posX, float posY);
    virtual unsigned char getPoints() = 0;
};