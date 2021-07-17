#pragma once
#include "../utils/punto.h"
#include "../utils/dimensiones.h"

const int ANCHO_MARTILLO = 16;
const int ALTO_MARTILLO = 16;

class Hammer
{
public:
    Hammer(punto_t pos) : pos(pos) {}
    dimensiones_t dimensions() const;
    void consume();
    punto_t pos;
private:
};