#include "../Mario.hpp"
#include "SaltandoState.h"
#include "ReposoState.h"
#include "CorriendoState.h"
#include "AireState.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "../../utils/Constants.hpp"

#define MARIO_VEL_SALTO 1
#define GRAVEDAD -0.03125
#define MARIO_VEL_X 0.5

SaltandoState* SaltandoState::instance;

SaltandoState::SaltandoState() {
    this->name = "Saltando";
}

SaltandoState* SaltandoState::getInstance() {
    if (SaltandoState::instance == NULL) {
        SaltandoState::instance = new SaltandoState();
    }

    return SaltandoState::instance;
}

void SaltandoState::setDir(char left, char right, float velX){
    this->left = left;
    this->right = right;
    this->velX = velX;
};


MarioState* SaltandoState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;

    AireState* aireState = AireState::getInstance();
    aireState->setDir(left, right, this->velY, this->velX);
    return aireState;
}

void SaltandoState::perform() {
    // TODO: actualizar a si está parado en una plataforma
    this->velY = MARIO_VEL_SALTO;
}

void SaltandoState::update() {}

char SaltandoState::getEstado() {
    return SALTANDO;
}