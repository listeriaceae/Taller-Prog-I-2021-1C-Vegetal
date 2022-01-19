#ifndef MARIO_VISTA_H
#define MARIO_VISTA_H

#include <SDL2/SDL.h>
#include "../utils/marioStructs.hpp"

class MarioVista
{
public:
  MarioVista();
  void mostrar(const PlayerState &estado);
  void setColor(int color);

private:
  SDL_Rect srcRect;
  SDL_Rect dstRect;
  SDL_RendererFlip flip{ SDL_FLIP_HORIZONTAL };
  int tiempo{};
  int hammerTime{};

  void updateReposo(Estado estado, ColliderType collider);
  void updateCorriendo(int nextX, ColliderType collider);
  void updateSaltando(int nextX);
  void updateTrepando(int nextY);
  void updateMuriendo(Estado estado);
  void updateNivelCompleto();
  void drawHammer();
};

#endif// MARIO_VISTA_H
