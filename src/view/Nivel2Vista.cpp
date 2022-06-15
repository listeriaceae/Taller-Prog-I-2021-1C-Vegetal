#include "Nivel2Vista.hpp"
#include "HammerVista.hpp"
#include "DefaultConfigVista.hpp"
#include "../utils/Constants.hpp"

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

Nivel2Vista::Nivel2Vista(std::size_t playerIndex_)
  : NivelVista{ playerIndex_ }, fuegoVista{ N2_POS_X_FUEGO, N2_POS_Y_FUEGO }, barrilVista{}
{
}

void Nivel2Vista::update(const GameState &state)
{
  {
    const SDL_Rect srcRect{ 224, 0, 224, 256 };
    SDL_RenderCopy(renderer, texture, &srcRect, NULL);
  }
  for (auto &pos : state.level.hammers)
    if (pos.y != 0)
      HammerVista::mostrar(pos);

  paulineVista.mostrar();
  dkVista.mostrar();
  fuegoVista.mostrar();

  if (defaultConfig)
    DefaultConfigVista::mostrar();

  barrilVista.startRender();
  for (const auto lvl = std::get_if<lv2>(&state.level.v);
       const auto &pos : *lvl) {
    if (pos.y == 0)
      break;
    barrilVista.mostrar(pos);
  }


  std::size_t i = 0;
  for (auto &player : this->jugadoresVista) {
    player.setColor((i + 1) * state.level.players[i].isEnabled);
    if (i != playerIndex)
      player.mostrar(state.level.players[i]);
    statsVista.mostrar(state.players[i], i);
    ++i;
  }
  jugadoresVista[playerIndex].mostrar(state.level.players[playerIndex]);
}
