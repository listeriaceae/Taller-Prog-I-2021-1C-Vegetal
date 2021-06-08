#include "../Mario.hpp"
#include "CorriendoState.h"
#include "SaltandoState.h"
#include "ReposoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

#define MARIO_VEL_X 0.5

CorriendoState* CorriendoState::instance;

CorriendoState::CorriendoState() {
    //std::cout << "CREANDO CorriendoState " << std::endl;
    this->name = "Corriendo";
}

CorriendoState* CorriendoState::getInstance() {
    if (CorriendoState::instance == NULL) {
        CorriendoState::instance = new CorriendoState();
    }

    return CorriendoState::instance;
}

void CorriendoState::setDir(char left, char right){
    this->left = left;
    this->right = right;
};

MarioState* CorriendoState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    char space = (controls & SPACE) != 0;

    if(space) return SaltandoState::getInstance();

    if(left || right) {
        CorriendoState* state = CorriendoState::getInstance();
        state->setDir(left, right);
        return state;
    }

    return ReposoState::getInstance();
}

void CorriendoState::perform() {
    this->velX = (this->right - this->left) * MARIO_VEL_X;
    //this->estadoEnSuelo = REPOSO + (CORRIENDO - REPOSO) * (this->velEnSuelo != 0);

    // TODO: actualizar a si está parado en una plataforma
    // if (this->estado != SALTANDO) {
    //     this->velX = this->velEnSuelo;
    //     this->estado = this->estadoEnSuelo;
    // }
}

void CorriendoState::update() {}