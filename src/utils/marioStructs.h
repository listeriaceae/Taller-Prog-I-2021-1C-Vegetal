#pragma once
#include "punto.h"

typedef struct estadoMario {
    punto_t pos;
    char estado;
} estadoMario_t;

typedef struct controls {
    unsigned int space : 1;
    unsigned int up : 1;
    unsigned int down : 1;
    unsigned int left : 1;
    unsigned int right : 1;
    unsigned int : 3;
}controls_t;