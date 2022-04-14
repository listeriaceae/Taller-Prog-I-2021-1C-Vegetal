#ifndef HAMMER_VISTA_H
#define HAMMER_VISTA_H

#include <SDL2/SDL.h>
#include "../utils/punto.hpp"

enum class EstadoHammer {
  LEVANTADO,
  GOLPEANDO
};

namespace HammerVista {
void mostrar(int x, int y, EstadoHammer estado, SDL_RendererFlip flip);
void mostrar(punto16_t pos);
}// namespace HammerVista

#endif// HAMMER_VISTA_H
