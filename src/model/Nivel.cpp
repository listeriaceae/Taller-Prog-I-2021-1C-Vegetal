#include "Nivel.h"

void Nivel::addPlayers(std::vector<Mario> &players) {
    this->players = &players;
    for (auto &player : players) {
        player.setStageAndReset(&stage);
    }
}

bool Nivel::isComplete() const {
    bool allMariosOnTop = true;
    for (auto &mario : *players) {
        // TODO: ajustar cuando algún Mario pierde todas las vidas
        allMariosOnTop &= mario.getIsLevelCompleted();
    }
    return allMariosOnTop;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}