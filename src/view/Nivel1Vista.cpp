#include "Nivel1Vista.h"
#include "PoleaVista.h"
#include "FuegoVista.h"
#include "PaulineVista.h"
#include "DonkeyKongVista.h"
#include "DefaultConfigVista.h"
#include "../utils/Constants.hpp"

Nivel1Vista::Nivel1Vista(SDL_Renderer *renderer, bool defaultConfig, const char* clientUsername)
: NivelVista(renderer) {
    strcpy(this->clientUsername, clientUsername);

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

    entidadesVista.push_back(new PaulineVista(renderer));
    entidadesVista.push_back(new DonkeyKongVista(renderer));

    if (defaultConfig) entidadesVista.push_back(new DefaultConfigVista(renderer));
}

void Nivel1Vista::update(estadoJuego_t *estadoJuego) {
    estadoNivel_t* estadoNivel = &(estadoJuego->estadoNivel);

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    for (EntidadEstaticaVista *vista : entidadesVista) {
        vista->mostrar();
    }

    for (punto_t pos : estadoNivel->platforms) {
        plataformaVista->mover(pos);
        plataformaVista->mostrar();
    }

    enemigoVista->startRender();
    for (punto_t pos : estadoNivel->enemies) {
        enemigoVista->mover(pos);
        enemigoVista->mostrar();
    }

    size_t i = 0;
    MarioVista* vistaJugadorPrincipal = NULL;
    estadoMario_t* estadoMarioPrincipal = NULL;
    for(MarioVista *player : this->jugadoresVista) {
        if(strcmp(estadoJuego->players[i].name, clientUsername) != 0) {
            estadoMario_t estado = estadoNivel->players[i];
            player->mostrar(estado.pos, estado.estado);
        }
        else {
            vistaJugadorPrincipal = player;
            estadoMarioPrincipal = &(estadoNivel->players[i]);
        }
        i++;
    }
    if(vistaJugadorPrincipal != NULL && estadoMarioPrincipal != NULL)
        vistaJugadorPrincipal->mostrar(estadoMarioPrincipal->pos, estadoMarioPrincipal->estado);
}

Nivel1Vista::~Nivel1Vista() {
    delete plataformaVista;
    delete enemigoVista;
}