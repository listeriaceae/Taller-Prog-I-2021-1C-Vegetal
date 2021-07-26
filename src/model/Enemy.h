#pragma once

#include "Entidad.h"

class Enemy : public Entidad
{
public:
    Enemy(float posX, float posY): Entidad(posX, posY) {};
    virtual unsigned char getPoints() = 0;
};