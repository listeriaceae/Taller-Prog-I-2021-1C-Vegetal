#include "Nivel.h"

void Nivel::addPlayers(std::vector<Mario> &players) {
    this->players = &players;
    for (auto &player : players) {
        player.setStageAndReset(&stage);
    }
}

bool Nivel::isComplete() const {
    bool allMariosHaveCompletedTheLevel = true;
    for (auto &mario : *players) {
        allMariosHaveCompletedTheLevel &= mario.getIsLevelCompleted();
    }
    return allMariosHaveCompletedTheLevel;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}