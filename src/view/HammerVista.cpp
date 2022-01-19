#include "HammerVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

static constexpr auto src_width = 16;
static constexpr auto src_height = 10;
static constexpr auto x_pos = 288;
static constexpr auto y_pos = 320;
static constexpr auto y_offset = 6;

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

static constexpr int dst_width =
  static_cast<int>(round(src_width * ANCHO_PANTALLA / (float)ANCHO_NIVEL));
static constexpr int dst_height =
  static_cast<int>(round(src_height * ALTO_PANTALLA / (float)ALTO_NIVEL));

void HammerVista::mostrar(int x, int y, EstadoHammer estado, SDL_RendererFlip flip)
{
  const SDL_Rect srcRect{
    x_pos + (static_cast<int>(estado) << 4), y_pos, src_width, src_height
  };
  const SDL_Rect dstRect = {
    x + static_cast<int>(estado) * dstRect.w * (flip == SDL_FLIP_NONE ? -1 : 1),
    y + static_cast<int>((y_offset * ALTO_PANTALLA / (float)ALTO_NIVEL) - (ALTO_MARIO * ALTO_PANTALLA / (float)ALTO_NIVEL) * (1 - static_cast<int>(estado))),
    dst_width,
    dst_height
  };
  SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0., NULL, flip);
}

void HammerVista::mostrar(punto16_t pos)
{
  static constexpr SDL_Rect srcRect{ x_pos, y_pos, src_width, src_height };
  const SDL_Rect dstRect = { static_cast<int>(round(from_fixed16<float>(pos.x) * (ANCHO_PANTALLA / (float)ANCHO_NIVEL))),
    static_cast<int>(round((from_fixed16<float>(pos.y) + y_offset) * (ALTO_PANTALLA / (float)ALTO_NIVEL))),
    dst_width,
    dst_height };
  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
