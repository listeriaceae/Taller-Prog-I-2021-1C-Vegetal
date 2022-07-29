#include <SDL2/SDL.h>
#include "PlataformaMovilVista.hpp"
#include "../utils/Constants.hpp"

#define PLATFORM_X_OFFSET 432
#define PLATFORM_Y_OFFSET 256

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void PlataformaMovilVista::mostrar(punto16_t pos)
{
  static constexpr SDL_Rect srcRect{
    PLATFORM_X_OFFSET, PLATFORM_Y_OFFSET, ANCHO_PLATAFORMA, ALTO_PLATAFORMA
  };
  const SDL_Rect dstRect{ from_fixed16<int>(pos.x),
    from_fixed16<int>(pos.y),
    ANCHO_PLATAFORMA,
    ALTO_PLATAFORMA };
  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
