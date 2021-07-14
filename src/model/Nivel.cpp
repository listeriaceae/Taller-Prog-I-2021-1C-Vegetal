#include "Nivel.h"

bool Nivel::isComplete() const {
    bool allMariosOnTop = true;
    for (auto &mario : *players){
        allMariosOnTop &= ((mario.pos.y <= 40) && mario.getIsLevelCompleted());
    }
    return allMariosOnTop;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}