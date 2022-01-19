#include <SDL2/SDL.h>
#include "TextRenderer.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define LETTER_X 7
#define LETTER_Y 7
#define LETTER_WIDTH 7
#define LETTER_HEIGHT 7
#define SPACING 2

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void TextRenderer::renderText(punto<int> punto, const char *text, float resize, Color color)
{
  SDL_Rect srcRect{ 0, 336, 7, 7 };
  srcRect.y = 336 + static_cast<int>(color) * LETTER_Y;

  SDL_Rect dstRect = { punto.x,
    punto.y,
    static_cast<int>(round(resize * (LETTER_WIDTH * ANCHO_PANTALLA / (float)ANCHO_NIVEL))),
    static_cast<int>(round(resize * (LETTER_HEIGHT * ALTO_PANTALLA / (float)ALTO_NIVEL))) };
  char c;
  while ((c = *text++) != '\0') {
    srcRect.x = get_chars().find_first_of(c) * LETTER_X;

    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    dstRect.x += round(resize * ((LETTER_WIDTH + SPACING) * ANCHO_PANTALLA / (float)ANCHO_NIVEL));
  }
}
