#ifndef POLEA_VISTA_H
#define POLEA_VISTA_H

#include <SDL2/SDL.h>

class PoleaVista
{
public:
  PoleaVista(int x, int y, int orientation, int rotation);
  void mostrar();

private:
  SDL_Rect rectDst;
  SDL_RendererFlip flip;
  int tiempo{};
};

#endif// POLEA_VISTA_H
