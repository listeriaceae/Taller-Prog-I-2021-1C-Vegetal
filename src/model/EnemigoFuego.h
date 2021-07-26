#pragma once
#include "Enemy.h"

class EnemigoFuego : public Enemy
{
public:
    EnemigoFuego(punto_t pos, int direccion, float min, float max);
    void mover();
    dimensiones_t dimensions() const;
    unsigned char getPoints();

private:
    float velX;
    float min, max;
};