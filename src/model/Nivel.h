#pragma once

#include <list>
#include "Mario.hpp"
#include "Entidad.h"
#include "EnemigoFuego.h"

struct estadoNivel {
        std::list<punto_t> platforms;
        std::list<punto_t> enemies;
        std::list<punto_t> barrels;
        std::list<estadoMario_t> players;
};

typedef struct estadoNivel estadoNivel_t;

class Nivel
{
    public:
        void addPlayer(Mario *jugador);
        void addEnemies(unsigned int amount);
        virtual void update() = 0;
        virtual estadoNivel_t* getEstado() = 0;
        virtual ~Nivel();

    protected:
        std::list<EnemigoFuego*> enemies;
        std::list<Mario*> jugadores;
        void updatePlayers();
};