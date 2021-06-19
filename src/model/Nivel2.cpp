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
    stage->addLadder(new Ladder(184, 227.75f, 203.25f));
    stage->addLadder(new Ladder(96, 197.75f, 167.25f));
    stage->addLadder(new Ladder(32, 193.75f, 171.25f));
    stage->addLadder(new Ladder(112, 166.25f, 132.75f));
    stage->addLadder(new Ladder(184, 161.75f, 137.25f));
    stage->addLadder(new Ladder(72, 130.25f, 102.75f));
    stage->addLadder(new Ladder(32, 127.75f, 105.25f));
    stage->addLadder(new Ladder(184, 95.75f, 71.25f));
    stage->addLadder(new Ladder(128, 68, 40));
}
const int MAX_BARRILES = 20;

void Nivel2::update() {
    if (++tick % 128 == 0) addBarrel();

    this->updateBarrels();
    for (Mario *mario : jugadores) mario->mover();
}

void Nivel2::addBarrel() {
    int x = rand() % (ANCHO_NIVEL - ANCHO_BARRIL);
    this->barriles.push_back(new Barril(x, N2_POS_Y_BARRIL));
}

void Nivel2::updateBarrels() {
    std::vector<Barril*>::iterator it;
    for (it = barriles.begin(); it != barriles.end();) {
        (*it)->mover();
        if (!(*it)->estaEnNivel()) {
            delete (*it);
            it = this->barriles.erase(it);
        } else ++it;
    }
}

estadoNivel_t* Nivel2::getEstado() {
    for (unsigned int i = 0; i < MAX_BARRILES; i++) {
        if(barriles.size() < i)
            estadoNivel->barrels[i] = barriles.at(i)->getPos();
    }
    for(unsigned int i = 0; i < this->jugadores.size(); i++) {
        estadoNivel->players[i] = jugadores.at(i)->getEstado();
    }

    return estadoNivel;
}

Nivel2::~Nivel2() {
    for (Barril *barril : barriles) delete barril;
    barriles.clear();
}