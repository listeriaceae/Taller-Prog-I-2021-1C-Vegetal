#include "../Mario.hpp"
#include "CorriendoLeftState.h"
#include "CorriendoRightState.h"
#include "SaltandoLeftState.h"
#include "ReposoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

#define MARIO_VEL_X 0.5
#define GRAVEDAD -0.03125

CorriendoLeftState* CorriendoLeftState::instance;

CorriendoLeftState::CorriendoLeftState() {
    //std::cout << "CREANDO CorriendoLeftState " << std::endl;
    this->name = "CorriendoLeft";
}

CorriendoLeftState* CorriendoLeftState::getInstance() {
    if (CorriendoLeftState::instance == NULL) {
        CorriendoLeftState::instance = new CorriendoLeftState();
    }

    return CorriendoLeftState::instance;
}

MarioState* CorriendoLeftState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    char space = (controls & SPACE) != 0;

    if(space) return SaltandoLeftState::getInstance();

    if(left) return CorriendoLeftState::getInstance();
    if(right) return CorriendoRightState::getInstance();

    return ReposoState::getInstance();
}

void CorriendoLeftState::perform() {
    this->velX = -MARIO_VEL_X;
    //this->estadoEnSuelo = REPOSO + (CORRIENDO - REPOSO) * (this->velEnSuelo != 0);
};

void CorriendoLeftState::update() {
}