#include "NivelVista.hpp"
#include "DefaultConfigVista.hpp"
#include "../configuration.hpp"
#include "../utils/Constants.hpp"

NivelVista::NivelVista(std::size_t playerIndex_)
  : SceneVista{}, playerIndex{ playerIndex_ },
    jugadoresVista{ configuration::GameConfiguration::getInstance(CONFIG_FILE).getMaxPlayers() },
    defaultConfig{
      configuration::GameConfiguration::getInstance(CONFIG_FILE).getDefaultConfigFlag()
    }
{
}
