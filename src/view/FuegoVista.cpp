#include "FuegoVista.hpp"
#include "../utils/Constants.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

FuegoVista::FuegoVista(int x, int y) : dstRect{ x, y, ANCHO_FUEGO, ALTO_FUEGO }
{}

void FuegoVista::mostrar()
{
  static constexpr auto frame_duration = 4;
  static constexpr auto frame_count = 4;
  tiempo = (tiempo + 1) & (frame_duration * frame_count - 1);

  static constexpr auto x_offset = 288;
  static constexpr auto y_offset = 304;
  const SDL_Rect srcRect{
    x_offset + ((tiempo & ~3) << 2), y_offset, ANCHO_FUEGO, ALTO_FUEGO
  };

  SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
