#include <SDL2/SDL.h>
#include "DonkeyKongVista.hpp"
#include "../utils/Constants.hpp"

#define DK_X_OFFSET 288
#define DK_Y_OFFSET 342

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void
DonkeyKongVista::mostrar()
{
  const int animate = ++counter < 96;
  const SDL_Rect srcRect{ DK_X_OFFSET + animate * DONKEYKONG_ANCHO,
                          DK_Y_OFFSET,
                          DONKEYKONG_ANCHO,
                          DONKEYKONG_ALTO };
  static constexpr SDL_Rect dstRect{
    DONKEYKONG_POS_X, DONKEYKONG_POS_Y, DONKEYKONG_ANCHO, DONKEYKONG_ALTO
  };
  SDL_RenderCopyEx(renderer,
                   texture,
                   &srcRect,
                   &dstRect,
                   0.,
                   NULL,
                   static_cast<SDL_RendererFlip>(animate && (counter & 32)));
}
