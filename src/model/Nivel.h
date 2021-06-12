#pragma once

#include <list>
#include "Mario.hpp"
#include "EnemigoFuego.h"
#include "stage/Stage.h"
#include "../utils/estadoNivel.h"

class Mario;

class Nivel
{
    public:
        Nivel();
        void addPlayer(Mario *jugador);
        virtual void update() = 0;
        virtual estadoNivel_t* getEstado() = 0;
        virtual ~Nivel();

    protected:
        Stage *stage;
        std::list<EnemigoFuego*> enemies;
        std::list<Mario*> jugadores;
        estadoNivel_t *estadoNivel;

        void updatePlayers();
        void updateEnemies();
};