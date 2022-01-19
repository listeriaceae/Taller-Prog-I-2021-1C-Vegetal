#include <SDL2/SDL.h>
#include "showMessage.hpp"
#include "TextRenderer.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

namespace showMessage {
void waitingLobby()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{ static_cast<int>(12 * ANCHO_PANTALLA / (float)ANCHO_NIVEL),
      static_cast<int>(112 * ALTO_PANTALLA / (float)ALTO_NIVEL) };
    TextRenderer::renderText(pos, "ESPERANDO A JUGADORES...", 1);
  }
  SDL_RenderPresent(renderer);
}

void disconnection()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{
      static_cast<int>(18.5f * ANCHO_PANTALLA / (float)ANCHO_NIVEL),
      static_cast<int>(112 * ALTO_PANTALLA / (float)ALTO_NIVEL)
    };
    TextRenderer::renderText(pos, "SE PERDIO LA CONEXION", 1);
  }
  {
    const punto<int> pos{
      static_cast<int>(45.5f * ANCHO_PANTALLA / (float)ANCHO_NIVEL),
      static_cast<int>(122 * ALTO_PANTALLA / (float)ALTO_NIVEL)
    };
    TextRenderer::renderText(pos, "CON EL SERVIDOR", 1);
  }
  SDL_RenderPresent(renderer);
}

void gameOver()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{ static_cast<int>(32 * ANCHO_PANTALLA / (float)ANCHO_NIVEL),
      static_cast<int>(112 * ALTO_PANTALLA / (float)ALTO_NIVEL) };
    TextRenderer::renderText(pos, "GAME OVER", 2);
  }
  SDL_RenderPresent(renderer);
}

void gameComplete()
{
  SDL_RenderClear(renderer);
  {
    const punto<int> pos{ static_cast<int>(36 * ANCHO_PANTALLA / (float)ANCHO_NIVEL),
      static_cast<int>(104 * ALTO_PANTALLA / (float)ALTO_NIVEL) };
    TextRenderer::renderText(pos, "FELICITACIONES", 1.25);
  }
  {
    const punto<int> pos{ static_cast<int>(24 * ANCHO_PANTALLA / (float)ANCHO_NIVEL),
      static_cast<int>(122 * ALTO_PANTALLA / (float)ALTO_NIVEL) };
    TextRenderer::renderText(pos, "JUEGO COMPLETADO", 1.25);
  }
  SDL_RenderPresent(renderer);
}
}// namespace showMessage
