#include "StatsVista.hpp"
#include "TextRenderer.hpp"
#include "../configuration.hpp"

#define MARGEN 4

#define POS_LEFT 4
#define POS_CENTER_LEFT 59
#define POS_CENTER 86
#define POS_CENTER_RIGHT 115
#define POS_RIGHT 170

#define OFFSET_SCORE_X 2
#define OFFSET_SCORE_Y 11

#define ANCHO_ICON 7
#define ANCHO_NOMBRE 27
#define ALTO_ICON 8

#define ICON_X_OFFSET 288
#define ICON_Y_OFFSET 330

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

StatsVista::StatsVista()
{
  switch (configuration::GameConfiguration::getInstance(CONFIG_FILE).getMaxPlayers()) {
  case 1:
    posiciones.assign({ POS_CENTER });
    break;
  case 2:
    posiciones.assign({ POS_LEFT, POS_RIGHT });
    break;
  case 3:
    posiciones.assign({ POS_LEFT, POS_CENTER, POS_RIGHT });
    break;
  case 4:
    posiciones.assign({ POS_LEFT, POS_CENTER_LEFT, POS_CENTER_RIGHT, POS_RIGHT });
    break;
  }
}

void StatsVista::mostrar(const PlayerInfo &estado, std::size_t nroJugador)
{
  const punto<int> top_left{ posiciones.at(nroJugador), MARGEN };
  const punto<int> score_pos{ top_left.x, top_left.y + OFFSET_SCORE_Y };
  const char score_str[7] = { '0',
    static_cast<char>('0' + (estado.score / 100) % 10),
    static_cast<char>('0' + (estado.score / 10) % 10),
    static_cast<char>('0' + estado.score % 10),
    '0',
    '0' };

  const SDL_Rect srcRect{ ICON_X_OFFSET + static_cast<int>(nroJugador) * ANCHO_ICON,
    ICON_Y_OFFSET,
    ANCHO_ICON,
    ALTO_ICON };
  SDL_Rect dstRect{ top_left.x + ANCHO_NOMBRE, 4, 7, 8 };
  for (int i = 0; i < estado.lives; ++i) {
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    dstRect.x += ANCHO_ICON;
  }

  TextRenderer::renderText(top_left, estado.name, 1, Color::WHITE);
  TextRenderer::renderText(score_pos, score_str, 1, Color::WHITE);
}
