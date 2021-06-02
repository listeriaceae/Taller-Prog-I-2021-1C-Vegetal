#pragma once

#include <list>
#include "Mario.hpp"
#include "EnemigoFuego.h"
#include "../utils/estadoNivel.h"

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
        void updateEnemies();
};