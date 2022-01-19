#include <SDL2/SDL.h>
#include "MarioController.hpp"

namespace MarioController {
unsigned char
  getControls()
{
  const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

  return keyboard[SDL_SCANCODE_SPACE] | keyboard[SDL_SCANCODE_UP] << 1 | keyboard[SDL_SCANCODE_DOWN] << 2 | keyboard[SDL_SCANCODE_LEFT] << 3 | keyboard[SDL_SCANCODE_RIGHT] << 4;
}
}// namespace MarioController
