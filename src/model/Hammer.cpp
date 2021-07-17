#include "Hammer.h"

dimensiones_t Hammer::dimensions() const {
    return {pos.x, pos.y, pos.x + (ANCHO_MARTILLO), pos.y + ALTO_MARTILLO};
}

void Hammer::consume() {
    pos = {0, 0};
}