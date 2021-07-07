#pragma once
#include "../utils/punto.h"

class Entidad
{
public:
    Entidad(float posX, float posY, int ancho, int alto);
    virtual void mover() = 0; //separar entidades en entidades estaticas y dinamicas
    inline punto_t getPos() const { return pos; }
    virtual ~Entidad() = default;
    punto_t pos;

protected:
    const int ancho;
    const int alto;
};