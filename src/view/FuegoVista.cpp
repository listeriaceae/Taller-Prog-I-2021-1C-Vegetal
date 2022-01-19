#include "FuegoVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

FuegoVista::FuegoVista(int x, int y)
  : dstRect{ static_cast<int>(round(x * (ANCHO_PANTALLA / (float)ANCHO_NIVEL))),
      static_cast<int>(round(y * (ALTO_PANTALLA / (float)ALTO_NIVEL))),
      static_cast<int>(round(ANCHO_FUEGO * ANCHO_PANTALLA / ANCHO_NIVEL)),
      static_cast<int>(round(ALTO_FUEGO * ALTO_PANTALLA / ALTO_NIVEL)) }
{
}

void FuegoVista::mostrar()
{
  static constexpr auto frame_duration = 4;
  static constexpr auto frame_count = 4;
  tiempo = (tiempo + 1) & (frame_duration * frame_count - 1);

  static constexpr auto x_offset = 288;
  static constexpr auto y_offset = 304;
  const SDL_Rect srcRect{ x_offset + ((tiempo & ~3) << 2), y_offset, ANCHO_FUEGO, ALTO_FUEGO };

  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
