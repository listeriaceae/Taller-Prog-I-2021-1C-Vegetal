#include "Nivel.h"

bool Nivel::isComplete() const {
    bool allMariosOnTop = true;
    for (auto &mario : *players){
        // TODO: ajustar cuando algún Mario pierde todas las vidas
        allMariosOnTop &= mario.getIsLevelCompleted();
    }
    return allMariosOnTop;
}

Nivel::~Nivel() {
    enemies.clear();
    platforms.clear();
}