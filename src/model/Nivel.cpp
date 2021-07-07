#include "Nivel.h"

bool Nivel::isComplete() const {
    bool result = false;
    for (Mario *mario : *players) result |= (mario->getPos().y == 40);
    return result;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}