#pragma once
#include <list>
#include "Nivel.h"
#include "Barril.h"

class Nivel2 : public Nivel
{
public:
    Nivel2();
    void addPlayers(std::vector<Mario> &players);
    void update();
    const estadoNivel_t &getEstado();
    void checkCollisions();

private:
    std::list<Barril> barriles;
    size_t tick = 0;

    void initPlatforms();
    void initLadders();
    void initHammers();

    void addBarrel();
    void updateBarrels();
};