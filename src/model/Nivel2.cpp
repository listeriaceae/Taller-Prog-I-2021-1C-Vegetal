#include "Nivel2.h"
#include "../utils/Constants.hpp"

Nivel2::Nivel2() : Nivel() {
    this->initPlatforms();
    this->initLadders();
}

void Nivel2::initPlatforms() {
    stage->addPlatform(new Platform(0, 248, 112, 248));
    stage->addPlatform(new Platform(112, 248, 224, 241));
    stage->addPlatform(new Platform(0, 208, 208, 221));
    stage->addPlatform(new Platform(16, 188, 224, 175));
    stage->addPlatform(new Platform(0, 142, 208, 155));
    stage->addPlatform(new Platform(16, 122, 224, 109));
    stage->addPlatform(new Platform(144, 85, 208, 89));
    stage->addPlatform(new Platform(0, 84, 144, 84));
}

void Nivel2::initLadders() {
    stage->addLadder(new Ladder(184, 227.5f, 203.5f));
    stage->addLadder(new Ladder(96, 198, 167));
    stage->addLadder(new Ladder(32, 194, 171));
    stage->addLadder(new Ladder(112, 166, 133));
    stage->addLadder(new Ladder(184, 161.5f, 137.5f));
    stage->addLadder(new Ladder(32, 128, 105));
    stage->addLadder(new Ladder(72, 130.5, 102.5f));
    stage->addLadder(new Ladder(184, 95.5f, 71.5f));
    stage->addLadder(new Ladder(128, 68, 40));
}

void Nivel2::update() {
    if (++tick % 128 == 0) addBarrel();

    this->updateBarrels();
    for (Mario *mario : jugadores) mario->mover();
}

void Nivel2::addBarrel() {
    int x = rand() % (ANCHO_NIVEL - ANCHO_BARRIL);
    this->barriles.push_front(new Barril(x, N2_POS_Y_BARRIL));
}

void Nivel2::updateBarrels() {
    std::list<Barril*>::iterator it;
    for (it = barriles.begin(); it != barriles.end();) {
        (*it)->mover();
        if (!(*it)->estaEnNivel()) {
            delete (*it);
            it = this->barriles.erase(it);
        } else ++it;
    }
}

estadoNivel_t* Nivel2::getEstado() {
    estadoNivel->barrels.clear();
    for (Barril *barril : this->barriles) {
        estadoNivel->barrels.push_back(barril->getPos());
    }
    estadoNivel->players.clear();
    for (Mario *player : this->jugadores) {
        estadoNivel->players.push_back(player->getEstado());
    }
    return estadoNivel;
}

Nivel2::~Nivel2() {
    for (Barril *barril : barriles) delete barril;
    barriles.clear();
}