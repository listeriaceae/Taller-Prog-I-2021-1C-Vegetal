#include "Nivel.h"

void Nivel::addPlayers(std::vector<Mario> &players) {
    this->players = &players;
    for (auto &player : players) {
        player.setStage(&stage);
        player.reset();
    }
}

bool Nivel::isComplete() const {
    bool result = false;
    for (auto &mario : *players) result |= (mario.pos.y <= 40);
    return result;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}