#include "Nivel.h"

Nivel::Nivel() {
    estadoNivel = new estadoNivel_t();
    stage = new Stage();
}

void Nivel::addPlayer(Mario *jugador) {
    jugador->setStage(stage);
    jugadores.push_back(jugador);
}

bool Nivel::isComplete() {
    bool result = false;
    for (Mario *mario : jugadores) result |= (mario->getPos().y <= 40.5);
    return result;
}

Nivel::~Nivel() {
    estadoNivel->barrels.clear();
    estadoNivel->enemies.clear();
    estadoNivel->platforms.clear();
    estadoNivel->players.clear();
    delete estadoNivel;

    delete stage;

    for (auto platform : platforms) delete platform;
    platforms.clear();

    for (auto enemy : enemies) delete enemy;
    enemies.clear();
    jugadores.clear();
}