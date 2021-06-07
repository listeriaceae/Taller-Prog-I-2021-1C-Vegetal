#include "../Mario.hpp"
#include "CorriendoLeftState.h"
#include "CorriendoRightState.h"
#include "SaltandoState.h"
#include "SaltandoRightState.h"
#include "ReposoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

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

    if(left) return CorriendoLeftState::getInstance();
    if(right) return SaltandoState::getInstance();

    return ReposoState::getInstance();
    
}

void SaltandoState::perform() {}

void SaltandoState::update() {}