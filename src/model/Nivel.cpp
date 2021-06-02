#include <stdlib.h>
#include "Nivel.h"
#include "../utils/Constants.hpp"
#include "../logger.h"

void Nivel::addPlayer(Mario *jugador) {
    jugadores.push_back(jugador);
}

void Nivel::addEnemies(unsigned int amount) {
    for (unsigned int i = 0; i < amount; ++i) {
        unsigned int j = rand() % plataformas.size();
        Plataforma *plataforma = plataformas[j];
        punto_t pos = plataforma->getPosicionAleatoria(ANCHO_ENEMIGO_FUEGO);
        pos.y -= ALTO_ENEMIGO_FUEGO;
        int direccion = (rand() % 2) ? -1 : 1;
        EnemigoFuego *enemy = new EnemigoFuego(pos, direccion);
        float min, max;
        plataforma->getLimites(&min, &max);
        enemy->setLimites(min, max);
        this->enemies.push_back(enemy);
    }
}

void Nivel::updatePlayers() {
    std::list<Mario*>::iterator it;
    for (it = jugadores.begin(); it != jugadores.end(); ++it) {
        (*it)->mover();
    }
}

void Nivel::updateEnemies() {
    std::list<EnemigoFuego*>::iterator it;
    for (it = enemies.begin(); it != enemies.end(); ++it) {
        (*it)->mover();
    }
}

Nivel::~Nivel() {
    jugadores.clear();

    std::vector<Plataforma*>::iterator it;
    for (it = plataformas.begin(); it != plataformas.end(); ++it) delete (*it);

    plataformas.clear();

    std::list<EnemigoFuego*>::iterator it2;
    for (it2 = enemies.begin(); it2 != enemies.end(); ++it2) delete (*it2);

    enemies.clear();
}