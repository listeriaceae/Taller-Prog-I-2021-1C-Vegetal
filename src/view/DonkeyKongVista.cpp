#include <SDL2/SDL.h>
#include "DonkeyKongVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define DK_X_OFFSET 288
#define DK_Y_OFFSET 342

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void DonkeyKongVista::mostrar()
{
  const int animate = ++counter < 96;
  const SDL_Rect srcRect{ DK_X_OFFSET + animate * DONKEYKONG_ANCHO,
    DK_Y_OFFSET,
    DONKEYKONG_ANCHO,
    DONKEYKONG_ALTO };
  static constexpr SDL_Rect dstRect{
    static_cast<int>(round(DONKEYKONG_POS_X * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
    static_cast<int>(round(DONKEYKONG_POS_Y * ALTO_PANTALLA / (float)ALTO_NIVEL)),
    static_cast<int>(round(DONKEYKONG_ANCHO * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
    static_cast<int>(round(DONKEYKONG_ALTO * ALTO_PANTALLA / (float)ALTO_NIVEL))
  };
  SDL_RenderCopyEx(renderer,
    texture,
    &srcRect,
    &dstRect,
    0.,
    NULL,
    static_cast<SDL_RendererFlip>(animate && (counter & 32)));
}
