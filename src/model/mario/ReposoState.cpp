#include "../Mario.hpp"
#include "ReposoState.h"
#include "CorriendoState.h"
#include "SaltandoState.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "../../utils/Constants.hpp"



ReposoState* ReposoState::instance;

ReposoState::ReposoState() : MarioState() {
    // std::cout << "CREANDO ReposoState " << std::endl;
    this->name = "Reposo";
}

ReposoState* ReposoState::getInstance() {
    if (ReposoState::instance == NULL) {
        ReposoState::instance = new ReposoState();
    }

    return ReposoState::instance;
}

MarioState* ReposoState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    char space = (controls & SPACE) != 0;

    if(left || right) {
        CorriendoState* state = CorriendoState::getInstance();
        state->setDir(left, right);
        return state;
    }

    if(space) return SaltandoState::getInstance();
 
    return ReposoState::instance;
}

void ReposoState::perform() {
}

void ReposoState::update() {  
}

char ReposoState::getEstado() {
    return REPOSO;
}