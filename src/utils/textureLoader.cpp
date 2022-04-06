#include <stdexcept>
#include <SDL2/SDL_image.h>
#include "textureLoader.hpp"
#include "../logger.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

namespace textureLoader {
void load()
{
  SDL_Surface *surface = IMG_Load("res/Images/DonkeyKong.png");

  if (surface == NULL) {
    logger::Logger::getInstance().logError("[client] Image file not found");
    throw std::runtime_error("Image file not found");
  }
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xf4, 0x43, 0x36));
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}
}// namespace textureLoader
