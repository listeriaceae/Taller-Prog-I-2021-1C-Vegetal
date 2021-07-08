#include "Nivel.h"

bool Nivel::isComplete() const {
    bool result = false;
    for (auto &mario : *players) result |= (mario.pos.y <= 40);
    return result;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}