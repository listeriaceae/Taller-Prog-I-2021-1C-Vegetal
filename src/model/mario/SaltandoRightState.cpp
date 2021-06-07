#include "../Mario.hpp"
#include "CorriendoLeftState.h"
#include "CorriendoRightState.h"
#include "SaltandoRightState.h"
#include "ReposoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

SaltandoRightState* SaltandoRightState::instance;

SaltandoRightState::SaltandoRightState() {
    this->name = "SaltandoRight";
}

SaltandoRightState* SaltandoRightState::getInstance() {
    if (SaltandoRightState::instance == NULL) {
        SaltandoRightState::instance = new SaltandoRightState();
    }

    return SaltandoRightState::instance;
}

MarioState* SaltandoRightState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;

    if(left) return CorriendoLeftState::getInstance();
    if(right) return SaltandoRightState::getInstance();

    return ReposoState::getInstance();
    
}

void SaltandoRightState::perform() {}

void SaltandoRightState::update() {  
}