#pragma once
#include <list>
#include "../utils/estadoMario.h"
#include "../utils/punto.h"

struct estadoNivel {
        std::list<punto_t> platforms;
        std::list<punto_t> enemies;
        std::list<punto_t> barrels;
        std::list<estadoMario_t> players;
};

typedef struct estadoNivel estadoNivel_t;
