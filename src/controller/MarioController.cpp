#include <SDL2/SDL.h>
#include "MarioController.hpp"
#include "AudioController.hpp"

namespace MarioController {
unsigned char
getControls()
{
  const auto *const keyboard = SDL_GetKeyboardState(NULL);

  AudioController::checkToggleMusicEvent(keyboard[SDL_SCANCODE_M]);
  return keyboard[SDL_SCANCODE_SPACE] << 0
       | keyboard[SDL_SCANCODE_UP]    << 1
       | keyboard[SDL_SCANCODE_DOWN]  << 2
       | keyboard[SDL_SCANCODE_LEFT]  << 3
       | keyboard[SDL_SCANCODE_RIGHT] << 4;
}
}// namespace MarioController
