#include <vector>
#include "Nivel1.h"
#include "../utils/Constants.hpp"
#include "../logger.h"

Nivel1::Nivel1() : Nivel() {
    this->initPlatforms();
    this->initLadders();
}

void Nivel1::initPlatforms() {
    for (unsigned int i = 0; i < 12; ++i) {
        MovingPlatform *platform = new MovingPlatform(i % 3, i / 3);
        movingPlatforms[i] = platform;
        this->stage->addMovingPlatform(platform);
    }

    this->stage->addPlatform(new Platform(0, 248, 48, 248));
    this->stage->addPlatform(new Platform(64, 248, 88, 248));
    this->stage->addPlatform(new Platform(104, 248, 128, 248));
    this->stage->addPlatform(new Platform(144, 248, 168, 248));
    this->stage->addPlatform(new Platform(184, 248, 224, 248));
    this->stage->addPlatform(new Platform(0, 200, 48, 200));
    this->stage->addPlatform(new Platform(64, 200, 88, 200));
    this->stage->addPlatform(new Platform(104, 200, 128, 200));
    this->stage->addPlatform(new Platform(144, 200, 168, 200));
    this->stage->addPlatform(new Platform(184, 200, 224, 200));
    this->stage->addPlatform(new Platform(0, 160, 16, 160));
    this->stage->addPlatform(new Platform(208, 160, 224, 160));
    this->stage->addPlatform(new Platform(0, 120, 16, 120));
    this->stage->addPlatform(new Platform(208, 120, 224, 120));
    this->stage->addPlatform(new Platform(208, 88, 224, 88));
    this->stage->addPlatform(new Platform(160, 87, 192, 87));
    this->stage->addPlatform(new Platform(24, 84, 144, 84));
}

void Nivel1::addEnemies(unsigned int amount) {
    std::vector<Platform *> *platforms = stage->getPlatforms();
    for (unsigned int i = 0; i < amount; ++i) {
        unsigned int j = 1 + (rand() % (platforms->size() - 1));           // Omite plataforma inicial
        Platform *platform = (*platforms)[j];
        punto_t pos = platform->getRandomPoint(ANCHO_ENEMIGO_FUEGO);
        pos.y -= ALTO_ENEMIGO_FUEGO;
        int direccion = (rand() % 2) ? -1 : 1;
        EnemigoFuego *enemy = new EnemigoFuego(pos, direccion);
        float min, max;
        platform->getLimits(&min, &max);
        enemy->setLimites(min, max);
        this->enemies.push_back(enemy);
    }
}

void Nivel1::update() {
    for (MovingPlatform *platform : movingPlatforms) platform->move();
    updateEnemies();
    updatePlayers();
}

estadoNivel_t* Nivel1::getEstado() {

    estadoNivel->enemies.clear();
    for (EnemigoFuego *enemy : this->enemies) {
        estadoNivel->enemies.push_back(enemy->getPos());
    }
    estadoNivel->platforms.clear();
    for (MovingPlatform *platform : this->movingPlatforms) {
        estadoNivel->platforms.push_back(platform->getPos());
    }
    estadoNivel->players.clear();
    for (Mario *player : this->jugadores) {
        estadoNivel->players.push_back(player->getEstado());
    }
    return estadoNivel;
}

Nivel1::~Nivel1() {
    for (MovingPlatform *platform : movingPlatforms) delete platform;
}