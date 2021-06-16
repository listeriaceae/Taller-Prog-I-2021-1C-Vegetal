#pragma once
#include <list>
#include "marioStructs.h"
#include "punto.h"

const int MAX_PLATFORMS = 12;
const int MAX_ENEMIES = 3;
const int MAX_BARRELS = 20;
const int MAX_PLAYERS = 2;

struct estadoNivel {
        punto_t platforms[MAX_PLATFORMS];
        punto_t enemies[MAX_ENEMIES];
        punto_t barrels[MAX_BARRELS];
        estadoMario_t players[MAX_PLAYERS];
};

typedef struct estadoNivel estadoNivel_t;
