#include "NivelVista.hpp"
#include "../configuration.hpp"
#include "../utils/Constants.hpp"

NivelVista::NivelVista(std::size_t playerIndex_)
  : SceneVista{}, playerIndex{ playerIndex_ }, jugadoresVista{
      configuration::getMaxPlayers()
    }
{}
