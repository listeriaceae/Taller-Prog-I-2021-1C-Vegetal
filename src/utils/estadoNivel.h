#pragma once
#include <list>
#include "marioStructs.h"
#include "punto.h"

struct estadoNivel {
        std::list<punto_t> platforms;
        std::list<punto_t> enemies;
        std::list<punto_t> barrels;
        std::list<estadoMario_t> players;
};

typedef struct estadoNivel estadoNivel_t;
