#include "../Mario.hpp"
#include "SaltandoState.h"
#include "AireState.h"
#include "ReposoState.h"
#include "CorriendoState.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "../../utils/Constants.hpp"

#define MARIO_VEL_SALTO 1
#define GRAVEDAD -0.03125

AireState* AireState::instance;

AireState::AireState() {
    this->name = "Aire";
}

AireState* AireState::getInstance() {
    if (AireState::instance == NULL) {
        AireState::instance = new AireState();
    }

    return AireState::instance;
}

void AireState::setDir(char left, char right, float velY, float velX){
    this->left = left;
    this->right = right;
    this->velY = velY;
    this->velX = velX;
};


MarioState* AireState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;

    // Mario esta en una plataforma?
    if (mario->getPos().y > 232) {
        return ReposoState::getInstance();
    }

    return AireState::getInstance();
}

void AireState::perform() {
}

void AireState::update() {
     this->velY += GRAVEDAD;
}

char AireState::getEstado() {
    return SALTANDO;
}