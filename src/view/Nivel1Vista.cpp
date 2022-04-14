#include "Nivel1Vista.hpp"
#include "PlataformaMovilVista.hpp"
#include "HammerVista.hpp"
#include "DefaultConfigVista.hpp"
#include "../utils/Constants.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

Nivel1Vista::Nivel1Vista(std::size_t playerIndex_)
  : NivelVista{ playerIndex_ }, poleas{ PoleaVista{ N1_POS_X1_POLEA, N1_POS_Y1_POLEA, 0, 0 },
      PoleaVista{ N1_POS_X2_POLEA, N1_POS_Y1_POLEA, 1, 0 },
      PoleaVista{ N1_POS_X1_POLEA, N1_POS_Y2_POLEA, 0, 1 },
      PoleaVista{ N1_POS_X2_POLEA, N1_POS_Y2_POLEA, 1, 1 } },
    fuegos{ FuegoVista{ N1_POS_X_FUEGO1, N1_POS_Y_FUEGO },
      FuegoVista{ N1_POS_X_FUEGO2, N1_POS_Y_FUEGO },
      FuegoVista{ N1_POS_X_FUEGO3, N1_POS_Y_FUEGO },
      FuegoVista{ N1_POS_X_FUEGO4, N1_POS_Y_FUEGO } },
    enemigosVista{ MAX_ENEMIES }
{
}

void Nivel1Vista::update(const GameState &state)
{
  {
    const SDL_Rect srcRect{ 0, 0, 224, 256 };
    SDL_RenderCopy(renderer, texture, &srcRect, NULL);
  }

  for (auto &pos : state.level.hammers)
    if (pos.y != 0)
      HammerVista::mostrar(pos);

  paulineVista.mostrar();
  dkVista.mostrar();

  if (defaultConfig)
    DefaultConfigVista::mostrar();

  for (auto &polea : poleas)
    polea.mostrar();

  for (auto &fuego : fuegos)
    fuego.mostrar();

  const auto &lvl = std::get<0>(state.level.v);
  for (auto &pos : lvl.platforms)
    PlataformaMovilVista::mostrar(pos);

  std::size_t i = 0;
  for (auto it = enemigosVista.begin(); it != enemigosVista.end();) {
    const auto &pos = lvl.enemies[i++];
    if (pos.y == 0)
      it = enemigosVista.erase(it);
    else
      (it++)->mostrar(pos);
  }


  i = 0;
  for (auto &player : this->jugadoresVista) {
    player.setColor((i + 1) * state.level.players[i].isEnabled);
    if (i != playerIndex)
      player.mostrar(state.level.players[i]);
    statsVista.mostrar(state.players[i], i);
    ++i;
  }
  jugadoresVista[playerIndex].mostrar(state.level.players[playerIndex]);
}
