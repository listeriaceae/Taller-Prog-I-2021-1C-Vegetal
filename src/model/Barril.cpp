#include "Barril.h"

#define VELOCIDAD_BARRIL 1

Barril::Barril(const float x, const float y)
: Entidad(x, y, ANCHO_BARRIL, ALTO_BARRIL), velX{0}, velY{VELOCIDAD_BARRIL} {}

void Barril::mover() {
    pos.y += this->velY;
}