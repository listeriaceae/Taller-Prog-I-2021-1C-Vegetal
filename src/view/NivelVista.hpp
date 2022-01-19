#ifndef NIVEL_VISTA_H
#define NIVEL_VISTA_H

#include <vector>
#include "SceneVista.hpp"
#include "MarioVista.hpp"
#include "StatsVista.hpp"
#include "PaulineVista.hpp"
#include "DonkeyKongVista.hpp"

class NivelVista : public SceneVista
{
public:
  NivelVista(std::size_t playerIndex);

protected:
  StatsVista statsVista{};
  PaulineVista paulineVista{};
  DonkeyKongVista dkVista{};
  std::size_t playerIndex;
  std::vector<MarioVista> jugadoresVista;
  bool defaultConfig;
};

#endif// NIVEL_VISTA_H
