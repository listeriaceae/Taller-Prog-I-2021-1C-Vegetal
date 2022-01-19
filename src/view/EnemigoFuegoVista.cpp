#include "EnemigoFuegoVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

EnemigoFuegoVista::EnemigoFuegoVista()
  : dstRect{ 0,
      0,
      static_cast<int>(round(ANCHO_ENEMIGO_FUEGO * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
      static_cast<int>(round(ALTO_ENEMIGO_FUEGO * ALTO_PANTALLA / (float)ALTO_NIVEL)) }
{
}

void EnemigoFuegoVista::mostrar(punto16_t pos)
{
  const int next_x = static_cast<int>(from_fixed16<float>(pos.x) * (ANCHO_PANTALLA / (float)ANCHO_NIVEL));
  const SDL_RendererFlip flip = static_cast<SDL_RendererFlip>(dstRect.x < next_x);
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
  dstRect.x = next_x;
  dstRect.y = static_cast<int>(from_fixed16<float>(pos.y) * (ALTO_PANTALLA / (float)ALTO_NIVEL));

  SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0.0, NULL, flip);
}
