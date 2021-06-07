#include "../Mario.hpp"
#include "CorriendoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

CorriendoState* CorriendoState::instance;

CorriendoState::CorriendoState() {
    std::cout << "CREANDO CorriendoState " << std::endl;
}

CorriendoState* CorriendoState::getInstance() {
    if (CorriendoState::instance == NULL) {
        CorriendoState::instance = new CorriendoState();
    }

    return CorriendoState::instance;
}

MarioState* CorriendoState::handleInput(char controls, Mario* mario) {
    // std::cout << "ReposoState: Atendiendo input -> " << controls << std::endl;
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    
}

void CorriendoState::perform() {}

void CorriendoState::update() {}