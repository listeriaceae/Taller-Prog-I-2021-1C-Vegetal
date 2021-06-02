#include "Nivel1Vista.h"
#include "PoleaVista.h"
#include "FuegoVista.h"
#include "PeachVista.h"
#include "DonkeyKongVista.h"
#include "DefaultConfigVista.h"
#include "../utils/Constants.hpp"

Nivel1Vista::Nivel1Vista(SDL_Renderer *renderer, bool defaultConfig)
: NivelVista(renderer) {

    plataformaVista = new PlataformaMovilVista(renderer);
    enemigoVista = new EnemigoFuegoVista(renderer);

    entidadesVista.push_back(new PoleaVista(N1_POSX1_POLEA, N1_POSY1_POLEA, 0, 0, renderer));
    entidadesVista.push_back(new PoleaVista(N1_POSX2_POLEA, N1_POSY1_POLEA, 1, 0, renderer));
    entidadesVista.push_back(new PoleaVista(N1_POSX1_POLEA, N1_POSY2_POLEA, 0, 1, renderer));
    entidadesVista.push_back(new PoleaVista(N1_POSX2_POLEA, N1_POSY2_POLEA, 1, 1, renderer));

    entidadesVista.push_back(new FuegoVista(N1_POSX_FUEGO1, N1_POSY_FUEGO, renderer));
    entidadesVista.push_back(new FuegoVista(N1_POSX_FUEGO2, N1_POSY_FUEGO, renderer));
    entidadesVista.push_back(new FuegoVista(N1_POSX_FUEGO3, N1_POSY_FUEGO, renderer));
    entidadesVista.push_back(new FuegoVista(N1_POSX_FUEGO4, N1_POSY_FUEGO, renderer));

    entidadesVista.push_back(new PeachVista(renderer));
    entidadesVista.push_back(new DonkeyKongVista(renderer));

    if (defaultConfig) entidadesVista.push_back(new DefaultConfigVista(renderer));
}

void Nivel1Vista::update(estadoNivel_t *estadoNivel) {
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    for (EntidadEstaticaVista *vista : entidadesVista) {
        vista->mostrar();
    }

    for (punto_t pos : estadoNivel->platforms) {
        plataformaVista->mover(pos);
        plataformaVista->mostrar();
    }

    enemigoVista->setTotal(estadoNivel->enemies.size());
    for (punto_t pos : estadoNivel->enemies) {
        enemigoVista->mover(pos);
        enemigoVista->mostrar();
    }

    size_t i = 0;
    for (estadoMario_t estadoMario : estadoNivel->players) {
        jugadoresVista.at(i++)->mostrar(estadoMario.pos, estadoMario.estado);
    }
}

Nivel1Vista::~Nivel1Vista() {
    delete plataformaVista;
    delete enemigoVista;
}