#ifndef STATS_VISTA_H
#define STATS_VISTA_H

#include <SDL2/SDL.h>
#include <vector>
#include "../utils/estadoJuego.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

class StatsVista
{
public:
  StatsVista();

  void mostrar(const PlayerInfo &estado, std::size_t nroJugador);

private:
  std::vector<int> posiciones{};
};

#endif// STATS_VISTA_H
