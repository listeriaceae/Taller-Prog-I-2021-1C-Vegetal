#include <SDL2/SDL.h>
#include "PaulineVista.hpp"
#include "../utils/Constants.hpp"

#define HELP_ANCHO 24
#define HELP_ALTO 8
#define HELP_POS_X 104
#define HELP_POS_Y 30

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void PaulineVista::mostrar()
{
  static constexpr SDL_Rect dstRect{
    PAULINE_POS_X, PAULINE_POS_Y, PAULINE_ANCHO, PAULINE_ALTO
  };
  static constexpr SDL_Rect helpDstRect{
    HELP_POS_X, HELP_POS_Y, HELP_ANCHO, HELP_ALTO
  };
  const SDL_Rect helpSrcRect{ 352, 282, HELP_ANCHO, HELP_ALTO };

  ++counter;
  int animate = 32 <= counter && counter < 96;
  const SDL_Rect srcRect{ 288 + ((animate & (1 - ((counter >> 3) & 1))) << 4),
    282,
    PAULINE_ANCHO,
    PAULINE_ALTO };
  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);

  if (animate) SDL_RenderCopy(renderer, texture, &helpSrcRect, &helpDstRect);
}
