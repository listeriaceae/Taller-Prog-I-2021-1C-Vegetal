#ifndef FUEGO_VISTA_H
#define FUEGO_VISTA_H

#include <SDL2/SDL.h>

class FuegoVista
{
public:
  FuegoVista(int x, int y);
  void mostrar();

private:
  SDL_Rect dstRect;
  int tiempo{};
};

#endif// FUEGO_VISTA_H
