#include "HammerVista.hpp"
#include "../utils/Constants.hpp"

static constexpr auto src_width = 16;
static constexpr auto src_height = 10;
static constexpr auto dst_width = src_width;
static constexpr auto dst_height = src_height;
static constexpr auto x_pos = 288;
static constexpr auto y_pos = 320;
static constexpr auto y_offset = 6;

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void HammerVista::mostrar(int x, int y, EstadoHammer estado, SDL_RendererFlip flip)
{
  const SDL_Rect srcRect{
    x_pos + (static_cast<int>(estado) * src_width), y_pos, src_width, src_height
  };
  const SDL_Rect dstRect = {
    x + static_cast<int>(estado) * ANCHO_MARIO * (flip == SDL_FLIP_NONE ? -1 : 1),
    y + y_offset - ALTO_MARIO * (1 - static_cast<int>(estado)),
    dst_width,
    dst_height
  };
  SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0., NULL, flip);
}

void HammerVista::mostrar(punto16_t pos)
{
  static constexpr SDL_Rect srcRect{ x_pos, y_pos, src_width, src_height };
  const SDL_Rect dstRect = { from_fixed16<int>(pos.x), from_fixed16<int>(pos.y) + y_offset,
                             dst_width, dst_height };
  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
