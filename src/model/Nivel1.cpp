#include "Nivel1.h"

Nivel1::Nivel1() : Nivel() {
    initPlataformas();
}

void Nivel1::initPlataformas() {
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

    this->plataformas.push_back(new Plataforma(0, 248, 48, 248));
    this->plataformas.push_back(new Plataforma(64, 248, 88, 248));
    this->plataformas.push_back(new Plataforma(104, 248, 128, 248));
    this->plataformas.push_back(new Plataforma(144, 248, 168, 248));
    this->plataformas.push_back(new Plataforma(184, 248, 224, 248));
    this->plataformas.push_back(new Plataforma(0, 200, 48, 200));
    this->plataformas.push_back(new Plataforma(64, 200, 88, 200));
    this->plataformas.push_back(new Plataforma(104, 200, 128, 200));
    this->plataformas.push_back(new Plataforma(144, 200, 168, 200));
    this->plataformas.push_back(new Plataforma(184, 200, 224, 200));
    this->plataformas.push_back(new Plataforma(0, 160, 16, 160));
    this->plataformas.push_back(new Plataforma(208, 160, 224, 160));
    this->plataformas.push_back(new Plataforma(0, 120, 16, 120));
    this->plataformas.push_back(new Plataforma(208, 120, 224, 120));
    this->plataformas.push_back(new Plataforma(208, 88, 224, 88));
    this->plataformas.push_back(new Plataforma(160, 87, 192, 87));
    this->plataformas.push_back(new Plataforma(24, 84, 144, 84));
    this->plataformas.push_back(new Plataforma(88, 56, 136, 56));
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