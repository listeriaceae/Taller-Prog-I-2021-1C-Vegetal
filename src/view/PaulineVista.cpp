#include <SDL2/SDL.h>
#include "PaulineVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define HELP_ANCHO 24
#define HELP_ALTO 8
#define HELP_POS_X 104
#define HELP_POS_Y 30

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void PaulineVista::mostrar()
{
  constexpr SDL_Rect dstRect{
    static_cast<int>(round(PAULINE_POS_X * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
    static_cast<int>(round(PAULINE_POS_Y * ALTO_PANTALLA / (float)ALTO_NIVEL)),
    static_cast<int>(round(PAULINE_ANCHO * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
    static_cast<int>(round(PAULINE_ALTO * ALTO_PANTALLA / (float)ALTO_NIVEL))
  };
  constexpr SDL_Rect helpDstRect{
    static_cast<int>(round(HELP_POS_X * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
    static_cast<int>(round(HELP_POS_Y * ALTO_PANTALLA / (float)ALTO_NIVEL)),
    static_cast<int>(round(HELP_ANCHO * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
    static_cast<int>(round(HELP_ALTO * ALTO_PANTALLA / (float)ALTO_NIVEL))
  };
  const SDL_Rect helpSrcRect{ 352, 282, HELP_ANCHO, HELP_ALTO };

  ++counter;
  int animate = 32 <= counter && counter < 96;
  const SDL_Rect srcRect{ 288 + ((animate & (1 - ((counter >> 3) & 1))) << 4),
    282,
    PAULINE_ANCHO,
    PAULINE_ALTO };
  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);

  if (animate)
    SDL_RenderCopy(renderer, texture, &helpSrcRect, &helpDstRect);
}
