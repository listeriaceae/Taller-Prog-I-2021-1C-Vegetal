#include <stdlib.h>
#include "Nivel.h"

Nivel::Nivel() {
    estadoNivel = new estadoNivel_t();
    stage = new Stage();
}

void Nivel::addPlayer(Mario *jugador) {
    jugadores.push_back(jugador);
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
    estadoNivel->barrels.clear();
    estadoNivel->enemies.clear();
    estadoNivel->platforms.clear();
    estadoNivel->players.clear();
    delete estadoNivel;

    delete stage;

    jugadores.clear();
    std::list<EnemigoFuego*>::iterator it2;
    for (it2 = enemies.begin(); it2 != enemies.end(); ++it2) delete (*it2);

    enemies.clear();
}