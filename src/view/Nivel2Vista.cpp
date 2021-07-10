#include "Nivel2Vista.h"
#include "FuegoVista.h"
#include "../configuration.hpp"
#include "../logger.h"
#include "../utils/Constants.hpp"

Nivel2Vista::Nivel2Vista(SDL_Renderer *renderer, const char* clientUsername)
: NivelVista(renderer, clientUsername) {

    const auto &stages = configuration::GameConfiguration::getInstance(CONFIG_FILE)->getStages();
    if (stages.size() > 1)
    {
        const std::string rutaImagen = stages.at(1).getBackgrounds().at(0);
        logger::Logger::getInstance().logDebug("Stage 2 background img: " + rutaImagen);
        this->setBackground(rutaImagen);
    }

    barrilVista = new BarrilVista(renderer);

    entidadesVista.push_back(new FuegoVista(N2_POS_X_FUEGO, N2_POS_Y_FUEGO, renderer));
}

void Nivel2Vista::update(const estadoJuego_t &estadoJuego) {
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    for (EntidadEstaticaVista *vista : entidadesVista) {
        vista->mostrar();
    }

    barrilVista->startRender();
    for (auto &pos : estadoJuego.estadoNivel.barrels) {
        if (pos.y == 0) break;
        barrilVista->mover(pos);
        barrilVista->mostrar();
    }

    size_t i = 0;
    MarioVista *vistaJugadorPrincipal{nullptr};
    const estadoMario_t *estadoMarioPrincipal{nullptr};
    for (auto &player : this->jugadoresVista) {
        player.setColor((i + 1) * estadoJuego.estadoNivel.players[i].isEnabled);
        if (strcmp(estadoJuego.players[i].name, clientUsername) != 0) {
            player.mostrar(estadoJuego.estadoNivel.players[i]);
        }
        else {
            vistaJugadorPrincipal = &player;
            estadoMarioPrincipal = &(estadoJuego.estadoNivel.players[i]);
        }
        ++i;
    }
    if (vistaJugadorPrincipal != nullptr && estadoMarioPrincipal != nullptr)
        vistaJugadorPrincipal->mostrar(*estadoMarioPrincipal);
}

Nivel2Vista::~Nivel2Vista() {
    delete barrilVista;
}