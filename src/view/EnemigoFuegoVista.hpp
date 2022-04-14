#ifndef ENEMIGO_FUEGO_VISTA_H
#define ENEMIGO_FUEGO_VISTA_H

#include <SDL2/SDL.h>
#include "../utils/punto.hpp"

class EnemigoFuegoVista
{
public:
  EnemigoFuegoVista();
  void mostrar(punto16_t pos);

private:
  int lastX{};
  int tiempo{};
};

#endif// ENEMIGO_FUEGO_VISTA_H
