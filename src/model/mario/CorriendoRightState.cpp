#include "../Mario.hpp"
#include "CorriendoLeftState.h"
#include "CorriendoRightState.h"
#include "ReposoState.h"
#include "SaltandoRightState.h"
#include <string>

#include <stdio.h>
#include <iostream>

CorriendoRightState* CorriendoRightState::instance;

CorriendoRightState::CorriendoRightState() {
    // std::cout << "CREANDO CorriendoRightState " << std::endl;
    this->name = "CorriendoRight";
}

CorriendoRightState* CorriendoRightState::getInstance() {
    if (CorriendoRightState::instance == NULL) {
        CorriendoRightState::instance = new CorriendoRightState();
    }

    return CorriendoRightState::instance;
}

MarioState* CorriendoRightState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    char space = (controls & SPACE) != 0;

    if(space) return SaltandoRightState::getInstance();

    if(left) return CorriendoLeftState::getInstance();
    if(right) return CorriendoRightState::getInstance();

    return ReposoState::getInstance();
    
}

void CorriendoRightState::perform() {}

void CorriendoRightState::update() {  
}