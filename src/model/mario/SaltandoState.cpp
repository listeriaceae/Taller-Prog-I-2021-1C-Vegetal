#include "../Mario.hpp"
#include "SaltandoState.h"
#include "ReposoState.h"
#include "CorriendoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

#define MARIO_VEL_SALTO 1
#define GRAVEDAD -0.03125

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

MarioState* SaltandoState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;

    if(left || right) {
        CorriendoState* state = CorriendoState::getInstance();
        state->setDir(left, right);
        return state;
    }

    return ReposoState::getInstance();
    
}

void SaltandoState::perform() {
    // TODO: actualizar a si está parado en una plataforma
    this->velY = MARIO_VEL_SALTO;
}

void SaltandoState::update() {}