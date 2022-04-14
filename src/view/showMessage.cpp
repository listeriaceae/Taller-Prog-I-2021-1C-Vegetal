#include <SDL2/SDL.h>
#include "showMessage.hpp"
#include "TextRenderer.hpp"
#include "../utils/Constants.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

namespace showMessage {
void waitingLobby()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{ 12, 112 };
    TextRenderer::renderText(pos, "ESPERANDO A JUGADORES...", 1);
  }
  SDL_RenderPresent(renderer);
}

void disconnection()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{ 18, 112 };
    TextRenderer::renderText(pos, "SE PERDIO LA CONEXION", 1);
  }
  {
    const punto<int> pos{ 45, 112 };
    TextRenderer::renderText(pos, "CON EL SERVIDOR", 1);
  }
  SDL_RenderPresent(renderer);
}

void gameOver()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{ 32, 112 };
    TextRenderer::renderText(pos, "GAME OVER", 2);
  }
  SDL_RenderPresent(renderer);
}

void gameComplete()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{ 36, 104 };
    TextRenderer::renderText(pos, "FELICITACIONES", 1.25);
  }
  {
    const punto<int> pos{ 24, 122 };
    TextRenderer::renderText(pos, "JUEGO COMPLETADO", 1.25);
  }
  SDL_RenderPresent(renderer);
}
}// namespace showMessage
