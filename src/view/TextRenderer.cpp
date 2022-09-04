#include <SDL2/SDL.h>
#include "TextRenderer.hpp"
#include "../utils/Constants.hpp"

#define LETTER_X 7
#define LETTER_Y 7
#define LETTER_WIDTH 7
#define LETTER_HEIGHT 7
#define SPACING 2

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void
TextRenderer::renderText(punto<int> punto,
                         std::string_view text,
                         float resize,
                         enum Color color)
{
  SDL_Rect srcRect{ 0, 336, LETTER_WIDTH, LETTER_HEIGHT };
  srcRect.y = 336 + color * LETTER_Y;

  SDL_Rect dstRect = { punto.x,
                       punto.y,
                       static_cast<int>(lround(resize * LETTER_WIDTH)),
                       static_cast<int>(lround(resize * LETTER_HEIGHT)) };

  const int step = static_cast<int>(lround(resize * (LETTER_WIDTH + SPACING)));
  for (const auto c : text) {
    srcRect.x = static_cast<int>(available_chars().find_first_of(c)) * LETTER_X;

    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    dstRect.x += step;
  }
}
