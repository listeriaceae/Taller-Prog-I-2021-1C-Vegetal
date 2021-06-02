#include "Nivel.h"
#include "../utils/Constants.hpp"

void Nivel::addPlayer(Mario *jugador) {
    jugadores.push_back(jugador);
}

void Nivel::addEnemies(unsigned int amount) {
    for (unsigned int i = 0; i < amount; ++i) {
        float x = (float)(rand() % (ANCHO_NIVEL - 32));
        float y = (float)(rand() % (ALTO_NIVEL - 32));
        int vel = (rand() % 2 == 0) ? -1 : 1;
        this->enemies.push_front(new EnemigoFuego(x, y, vel));
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

    std::list<EnemigoFuego*>::iterator it2;
    for (it2 = enemies.begin(); it2 != enemies.end(); ++it2) delete (*it2);

    enemies.clear();
}