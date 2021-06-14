#pragma once
#include <list>
#include <vector>
#include "stage/Stage.h"
#include "Mario.hpp"
#include "EnemigoFuego.h"
#include "../utils/estadoNivel.h"

class Mario;

class Nivel
{
    public:
        Nivel();
        void addPlayer(Mario *jugador);
        virtual void update() = 0;
        virtual estadoNivel_t* getEstado() = 0;
        bool isComplete();
        virtual ~Nivel();

    protected:
        Stage *stage;
        std::vector<Platform *> platforms;
        std::list<Mario *> jugadores;
        std::list<EnemigoFuego *> enemies;
        estadoNivel_t *estadoNivel;
};