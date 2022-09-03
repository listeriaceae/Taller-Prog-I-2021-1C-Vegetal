#include "InterludeVista.hpp"
#include "TextRenderer.hpp"
#include "../configuration.hpp"
#include "../utils/Constants.hpp"

#define X_POS_CONGRATS 28
#define Y_POS_CONGRATS 36
#define X_POS_GAME_OVER 72
#define Y_POS_GAME_OVER 48

#define X_POS_USER 48
#define Y_POS_USER 100
#define Y_DIF_USERS 20
#define OFFSET_SCORE 64

InterludeVista::InterludeVista()
  : SceneVista{}, maxPlayers{ configuration::getMaxPlayers() }
{}

void
InterludeVista::update(const GameState &estadoJuego)
{
  punto<int> statsJugadorPos{ X_POS_USER, Y_POS_USER };

  TextRenderer::renderText(statsJugadorPos, "USER", 1.25f, Color::YELLOW);
  TextRenderer::renderText(
    { statsJugadorPos.x + OFFSET_SCORE, statsJugadorPos.y },
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

    TextRenderer::renderText(
      { statsJugadorPos.x + OFFSET_SCORE, statsJugadorPos.y },
      score_str,
      1.25f,
      Color::LIME);
  }
}
