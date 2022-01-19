#include <SDL2/SDL.h>
#include "BarrilVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void BarrilVista::mostrar(punto16_t pos)
{
  static constexpr int width =
    static_cast<int>(round(ANCHO_BARRIL * ANCHO_PANTALLA / (float)ANCHO_NIVEL));
  static constexpr int height =
    static_cast<int>(round(ALTO_BARRIL * ALTO_PANTALLA / (float)ALTO_NIVEL));
  const SDL_Rect dstRect = { static_cast<int>(from_fixed16<float>(pos.x) * (ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
    static_cast<int>(from_fixed16<float>(pos.y) * (ALTO_PANTALLA / (float)ALTO_NIVEL)),
    width,
    height };
  const auto flip =
    static_cast<SDL_RendererFlip>((to_fixed16(110 - ALTO_BARRIL) < pos.y && pos.y < to_fixed16(142.75f - ALTO_BARRIL)) || (to_fixed16(175.5f - ALTO_BARRIL) < pos.y && pos.y < to_fixed16(208.25f - ALTO_BARRIL)));

  static constexpr auto frame_duration = 4;
  static constexpr auto frame_count = 4;
  tiempo = (tiempo + update) & (frame_duration * frame_count - 1);

  static constexpr auto x_offset = 288;
  static constexpr auto y_offset = 374;
  static constexpr auto sprite_gap_size = 12;

  const SDL_Rect srcRect = {
    x_offset + (tiempo >> 2) * sprite_gap_size, y_offset, ANCHO_BARRIL, ALTO_BARRIL
  };
  SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0., NULL, flip);
  update = 0;
}
