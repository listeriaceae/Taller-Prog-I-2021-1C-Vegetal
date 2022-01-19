#include "InterludeVista.hpp"
#include "TextRenderer.hpp"
#include "../configuration.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define X_POS_CONGRATS static_cast<int>(28 * ANCHO_PANTALLA / (float)ANCHO_NIVEL)
#define Y_POS_CONGRATS static_cast<int>(36 * ALTO_PANTALLA / (float)ALTO_NIVEL)
#define X_POS_GAME_OVER static_cast<int>(72 * ANCHO_PANTALLA / (float)ANCHO_NIVEL)
#define Y_POS_GAME_OVER static_cast<int>(48 * ALTO_PANTALLA / (float)ALTO_NIVEL)

#define X_POS_USER static_cast<int>(48 * ANCHO_PANTALLA / (float)ANCHO_NIVEL)
#define Y_POS_USER static_cast<int>(100 * ALTO_PANTALLA / (float)ALTO_NIVEL)
#define Y_DIF_USERS static_cast<int>(20 * ALTO_PANTALLA / (float)ALTO_NIVEL)
#define OFFSET_SCORE static_cast<int>(64 * ANCHO_PANTALLA / (float)ANCHO_NIVEL)

InterludeVista::InterludeVista()
  : SceneVista{}, maxPlayers{
      configuration::GameConfiguration::getInstance(CONFIG_FILE).getMaxPlayers()
    }
{
}

void InterludeVista::update(const GameState &estadoJuego)
{
  punto<int> statsJugadorPos{ X_POS_USER, Y_POS_USER };

  TextRenderer::renderText(statsJugadorPos, "USER", 1.25f, Color::YELLOW);
  TextRenderer::renderText({ statsJugadorPos.x + OFFSET_SCORE, statsJugadorPos.y },
    "SCORE",
    1.25f,
    Color::YELLOW);

  for (std::size_t i = 0; i < maxPlayers; ++i) {
    statsJugadorPos.y += Y_DIF_USERS;
    TextRenderer::renderText(
      statsJugadorPos, estadoJuego.players[i].name, 1.25f, Color::MAGENTA);
    const char score_str[7] = {
      '0',
      static_cast<char>('0' + (estadoJuego.players[i].score / 100) % 10),
      static_cast<char>('0' + (estadoJuego.players[i].score / 10) % 10),
      static_cast<char>('0' + estadoJuego.players[i].score % 10),
      '0',
      '0'
    };

    TextRenderer::renderText({ statsJugadorPos.x + OFFSET_SCORE, statsJugadorPos.y },
      score_str,
      1.25f,
      Color::LIME);
  }
}
