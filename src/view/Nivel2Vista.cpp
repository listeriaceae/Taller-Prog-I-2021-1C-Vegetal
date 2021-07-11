#include "Nivel2Vista.h"
#include "FireBarrelVista.h"
#include "FuegoVista.h"
#include "PaulineVista.h"
#include "DonkeyKongVista.h"
#include "DefaultConfigVista.h"
#include "../controller/AudioController.h"
#include "../utils/Constants.hpp"

Nivel2Vista::Nivel2Vista(SDL_Renderer *renderer, bool defaultConfig, const char* clientUsername)
: NivelVista(renderer) {
    strcpy(this->clientUsername, clientUsername);

    barrilVista = new BarrilVista(renderer);

    entidadesVista.push_back(new FireBarrelVista(renderer));
    entidadesVista.push_back(new FuegoVista(N2_POS_X_FUEGO, N2_POS_Y_FUEGO, renderer));

    entidadesVista.push_back(new PaulineVista(renderer));
    entidadesVista.push_back(new DonkeyKongVista(renderer));

    if (defaultConfig) entidadesVista.push_back(new DefaultConfigVista(renderer));

}

void Nivel2Vista::update(estadoJuego_t *estadoJuego) {
    estadoNivel_t* estadoNivel = &(estadoJuego->estadoNivel);

    for(unsigned int j = 0; j < this->jugadoresVista.size(); j++) {
        if(strcmp(estadoJuego->players[j].name, clientUsername) == 0) {
            AudioController::playSounds(estadoNivel->players[j].sounds);
        }
    }

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    for (EntidadEstaticaVista *vista : entidadesVista) {
        vista->mostrar();
    }

    barrilVista->startRender();
    for (punto_t pos : estadoNivel->barrels) {
        if (pos.y == 0) break;
        barrilVista->mover(pos);
        barrilVista->mostrar();
    }

    size_t i = 0;
    MarioVista* vistaMarioCliente = NULL;
    estadoMario_t* estadoMarioCliente = NULL;
    for(MarioVista *player : this->jugadoresVista) {
        if(strcmp(estadoJuego->players[i].name, clientUsername) != 0) {
            estadoMario_t estado = estadoNivel->players[i];
            player->mostrar(estado.pos, estado.estado);
        }
        else {
            vistaMarioCliente = player;
            estadoMarioCliente = &(estadoNivel->players[i]);
        }
        i++;
    }
    if(vistaMarioCliente != NULL && estadoMarioCliente != NULL)
        vistaMarioCliente->mostrar(estadoMarioCliente->pos, estadoMarioCliente->estado);
}

Nivel2Vista::~Nivel2Vista() {
    delete barrilVista;
}
