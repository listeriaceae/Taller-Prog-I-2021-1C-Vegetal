#include <iostream>
#include "Nivel1Vista.h"
#include "PoleaVista.h"
#include "FuegoVista.h"
#include "../configuration.hpp"
#include "../logger.h"
#include "../utils/Constants.hpp"

Nivel1Vista::Nivel1Vista(SDL_Renderer *renderer, const char* clientUsername)
: NivelVista(renderer, clientUsername) {

    const auto &stages = configuration::GameConfiguration::getInstance(CONFIG_FILE)->getStages();
    if (stages.size() > 0)
    {
        const std::string rutaImagen = stages.at(0).getBackgrounds().at(0);
        logger::Logger::getInstance().logDebug("Stage 1 background img: " + rutaImagen);
        this->setBackground(rutaImagen);
    }

    plataformaVista = new PlataformaMovilVista(renderer);
    enemigoVista = new EnemigoFuegoVista(renderer);

    entidadesVista.push_back(new PoleaVista(N1_POS_X1_POLEA, N1_POS_Y1_POLEA, 0, 0, renderer));
    entidadesVista.push_back(new PoleaVista(N1_POS_X2_POLEA, N1_POS_Y1_POLEA, 1, 0, renderer));
    entidadesVista.push_back(new PoleaVista(N1_POS_X1_POLEA, N1_POS_Y2_POLEA, 0, 1, renderer));
    entidadesVista.push_back(new PoleaVista(N1_POS_X2_POLEA, N1_POS_Y2_POLEA, 1, 1, renderer));

    entidadesVista.push_back(new FuegoVista(N1_POS_X_FUEGO1, N1_POS_Y_FUEGO, renderer));
    entidadesVista.push_back(new FuegoVista(N1_POS_X_FUEGO2, N1_POS_Y_FUEGO, renderer));
    entidadesVista.push_back(new FuegoVista(N1_POS_X_FUEGO3, N1_POS_Y_FUEGO, renderer));
    entidadesVista.push_back(new FuegoVista(N1_POS_X_FUEGO4, N1_POS_Y_FUEGO, renderer));
}

void Nivel1Vista::update(const estadoJuego_t &estadoJuego) {
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    for (EntidadEstaticaVista *vista : entidadesVista) {
        vista->mostrar();
    }

    for (auto &pos : estadoJuego.estadoNivel.platforms) {
        plataformaVista->mover(pos);
        plataformaVista->mostrar();
    }

    enemigoVista->startRender();
    for (auto &pos : estadoJuego.estadoNivel.enemies) {
        enemigoVista->mover(pos);
        enemigoVista->mostrar();
    }

    size_t i = 0;
    MarioVista *vistaJugadorPrincipal{nullptr};
    const estadoMario_t *estadoMarioPrincipal{nullptr};
    for (auto &player : this->jugadoresVista) {
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

Nivel1Vista::~Nivel1Vista() {
    delete plataformaVista;
    delete enemigoVista;
}