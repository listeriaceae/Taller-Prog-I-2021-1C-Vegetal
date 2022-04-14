#include "EnemigoFuegoVista.hpp"
#include "../utils/Constants.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

EnemigoFuegoVista::EnemigoFuegoVista()
{
}

void EnemigoFuegoVista::mostrar(punto16_t pos)
{
  const SDL_RendererFlip flip = static_cast<SDL_RendererFlip>(
                                  lastX < pos.x);
  lastX = pos.x;
  static constexpr auto frame_duration = 8;
  static constexpr auto frame_count = 2;
  tiempo = (tiempo + 1) & (frame_duration * frame_count - 1);

  static constexpr auto x_offset = 288;
  static constexpr auto y_offset = 266;
  static constexpr auto sprite_gap_size = 15;
  const SDL_Rect srcRect = { x_offset + (tiempo >> 3) * sprite_gap_size,
    y_offset,
    ANCHO_ENEMIGO_FUEGO,
    ALTO_ENEMIGO_FUEGO };
  const SDL_Rect dstRect{ from_fixed16<int>(pos.x),
                          from_fixed16<int>(pos.y),
                          ANCHO_ENEMIGO_FUEGO,
                          ALTO_ENEMIGO_FUEGO
  };

  SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0.0, NULL, flip);
}
