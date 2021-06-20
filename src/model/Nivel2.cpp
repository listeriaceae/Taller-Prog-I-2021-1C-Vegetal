#include "Nivel2.h"
#include "../utils/Constants.hpp"

Nivel2::Nivel2() : Nivel() {
    this->initPlatforms();
    this->initLadders();
}

void Nivel2::initPlatforms() {
    stage->addPlatform(new Platform(0, 248, 120, 248));
    stage->addPlatform(new Platform(112, 248, 224, 241));
    stage->addPlatform(new Platform(0, 208, 208, 221));
    stage->addPlatform(new Platform(16, 188, 224, 175));
    stage->addPlatform(new Platform(0, 142, 208, 155));
    stage->addPlatform(new Platform(16, 122, 224, 109));
    stage->addPlatform(new Platform(136, 84.5, 208, 89));
    stage->addPlatform(new Platform(0, 84, 130, 84));
}

void Nivel2::initLadders() {
    stage->addLadder(new Ladder(180, 227.75f, 203.25f));
    stage->addLadder(new Ladder(92, 197.75f, 167.25f));
    stage->addLadder(new Ladder(28, 193.75f, 171.25f));
    stage->addLadder(new Ladder(108, 166.25f, 132.75f));
    stage->addLadder(new Ladder(180, 161.75f, 137.25f));
    stage->addLadder(new Ladder(68, 130.25f, 102.75f));
    stage->addLadder(new Ladder(28, 127.75f, 105.25f));
    stage->addLadder(new Ladder(180, 95.75f, 71.25f));
    stage->addLadder(new Ladder(124, 68, 40));
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