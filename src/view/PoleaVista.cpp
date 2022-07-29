#include "PoleaVista.hpp"
#include "../utils/Constants.hpp"

#define TIEMPO_POR_FRAME 16
#define CANT_FRAMES 3
#define POLEA_X_OFFSET 288
#define POLEA_Y_OFFSET 256

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

PoleaVista::PoleaVista(int x, int y, int orientation, int rotation)
  : rectDst{ x, y, ANCHO_POLEA, ALTO_POLEA }, flip{
      static_cast<SDL_RendererFlip>(
        ((orientation << 1) | orientation) ^ ((1 - rotation) << 1))
    }
{}

void PoleaVista::mostrar()
{
  tiempo = (tiempo + 1) % (TIEMPO_POR_FRAME * CANT_FRAMES);
  const SDL_Rect rectSrc{ POLEA_X_OFFSET
                            + (tiempo / TIEMPO_POR_FRAME) * ANCHO_POLEA,
    POLEA_Y_OFFSET,
    ANCHO_POLEA,
    ALTO_POLEA };

  SDL_RenderCopyEx(renderer, texture, &rectSrc, &rectDst, 0, NULL, flip);
}
