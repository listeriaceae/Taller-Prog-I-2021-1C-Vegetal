#pragma once

#include <list>
#include <vector>
#include "Mario.hpp"
#include "EnemigoFuego.h"
#include "Plataforma.h"
#include "../utils/estadoNivel.h"
#include "nivel/Escalera.h"
#include <map>

class Mario;

class Nivel
{
    public:
        void addPlayer(Mario *jugador);
        void addEnemies(unsigned int amount);
        virtual void update() = 0;
        virtual estadoNivel_t* getEstado() = 0;
        virtual ~Nivel();
        virtual Escalera* getEscalera(punto_t p) = 0;

    protected:
        std::vector<Plataforma*> plataformas;
        std::list<EnemigoFuego*> enemies;
        std::list<Mario*> jugadores;
        std::map<int, Escalera*> escaleras;

        void updatePlayers();
        void updateEnemies();
};