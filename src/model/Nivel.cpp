#include "Nivel.h"

void Nivel::addPlayers(std::vector<Mario> &players) {
    this->players = &players;
    for (auto &player : players) {
        player.setStage(&stage);
        player.reset();
    }
}

bool Nivel::isComplete() const {
    bool allMariosOnTop = true;
    for (auto &mario : *players) {
        allMariosOnTop &= ((mario.pos.y <= 40) && mario.getIsLevelCompleted());
    }
    return allMariosOnTop;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}