#include "../Mario.hpp"
#include "CorriendoLeftState.h"
#include "CorriendoRightState.h"
#include "SaltandoRightState.h"
#include "SaltandoLeftState.h"
#include "ReposoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

SaltandoLeftState* SaltandoLeftState::instance;

SaltandoLeftState::SaltandoLeftState() {
    this->name = "SaltandoRight";
}

SaltandoLeftState* SaltandoLeftState::getInstance() {
    if (SaltandoLeftState::instance == NULL) {
        SaltandoLeftState::instance = new SaltandoLeftState();
    }

    return SaltandoLeftState::instance;
}

MarioState* SaltandoLeftState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;

    if(left) return CorriendoLeftState::getInstance();
    if(right) return CorriendoRightState::getInstance();

    return ReposoState::getInstance();
}

void SaltandoLeftState::perform() {}

void SaltandoLeftState::update() {  
}