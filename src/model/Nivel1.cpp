#include "Nivel1.h"

Nivel1::Nivel1() : Nivel() {
    plataformasMoviles.push_back(new PlataformaMovil(0, 0));
    plataformasMoviles.push_back(new PlataformaMovil(1, 0));
    plataformasMoviles.push_back(new PlataformaMovil(2, 0));

    plataformasMoviles.push_back(new PlataformaMovil(0, 1));
    plataformasMoviles.push_back(new PlataformaMovil(1, 1));
    plataformasMoviles.push_back(new PlataformaMovil(2, 1));

    plataformasMoviles.push_back(new PlataformaMovil(0, 2));
    plataformasMoviles.push_back(new PlataformaMovil(1, 2));
    plataformasMoviles.push_back(new PlataformaMovil(2, 2));

    plataformasMoviles.push_back(new PlataformaMovil(0, 3));
    plataformasMoviles.push_back(new PlataformaMovil(1, 3));
    plataformasMoviles.push_back(new PlataformaMovil(2, 3));
}

void Nivel1::update() {
    updatePlatforms();
    updateEnemies();
    updatePlayers();
}

void Nivel1::updatePlatforms() {
    std::list<PlataformaMovil*>::iterator it;
    for (it = plataformasMoviles.begin(); it != plataformasMoviles.end(); ++it) {
        (*it)->mover();
    }
}

estadoNivel_t* Nivel1::getEstado() {
    estadoNivel_t *estado = new estadoNivel_t();

    for (EnemigoFuego *enemy : this->enemies) {
        estado->enemies.push_back(enemy->getPos());
    }
    for (PlataformaMovil *plataforma : this->plataformasMoviles) {
        estado->platforms.push_back(plataforma->getPos());
    }
    for (Mario *player : this->jugadores) {
        estado->players.push_back(player->getEstado());
    }
    return estado;
}

Nivel1::~Nivel1() {
    std::list<PlataformaMovil*>::iterator it;
    for (it = plataformasMoviles.begin(); it != plataformasMoviles.end(); ++it) delete (*it);

    plataformasMoviles.clear();
}