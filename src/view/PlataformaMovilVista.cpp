#include <SDL2/SDL.h>
#include "PlataformaMovilVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define PLATFORM_X_OFFSET 432
#define PLATFORM_Y_OFFSET 256

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void PlataformaMovilVista::mostrar(punto16_t pos)
{
  const SDL_Rect srcRect{
    PLATFORM_X_OFFSET, PLATFORM_Y_OFFSET, ANCHO_PLATAFORMA, ALTO_PLATAFORMA
  };
  constexpr int width =
    static_cast<int>(round(ANCHO_PLATAFORMA * ANCHO_PANTALLA / (float)ANCHO_NIVEL));
  constexpr int height =
    static_cast<int>(round(ALTO_PLATAFORMA * ALTO_PANTALLA / (float)ALTO_NIVEL));
  const SDL_Rect dstRect{ static_cast<int>(round(from_fixed16<float>(pos.x) * (ANCHO_PANTALLA / (float)ANCHO_NIVEL))),
    static_cast<int>(round(from_fixed16<float>(pos.y) * (ALTO_PANTALLA / (float)ALTO_NIVEL))),
    width,
    height };
  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
