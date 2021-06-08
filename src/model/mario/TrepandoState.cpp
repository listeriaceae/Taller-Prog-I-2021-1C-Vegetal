#include "../Mario.hpp"
#include "TrepandoState.h"
#include "CorriendoState.h"
#include "SaltandoState.h"
#include "ReposoState.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "../../utils/Constants.hpp"

#define MARIO_VELOCIDAD 0.5

TrepandoState* TrepandoState::instance;

TrepandoState::TrepandoState() {
    this->name = "Trepando";
}

TrepandoState* TrepandoState::getInstance() {
    if (TrepandoState::instance == NULL) {
        TrepandoState::instance = new TrepandoState();
    }

    return TrepandoState::instance;
}

void TrepandoState::setDir(char up, char down){
    this->up = up;
    this->down = down;
};

MarioState* TrepandoState::handleInput(char controls, Mario* mario) {
    char left = (controls & LEFT) != 0;
    char right = (controls & RIGHT) != 0;
    char space = (controls & SPACE) != 0;

    char up = (controls & UP) != 0;
    char down = (controls & DOWN) != 0;

    if(space) {
        SaltandoState* saltandoState = SaltandoState::getInstance();
        saltandoState->setDir(left, right, this->velX);
        return saltandoState;
    }

    if(left || right) {
        CorriendoState* corriendoState = CorriendoState::getInstance();
        corriendoState->setDir(left, right);
        return corriendoState;
    }

     if (up || down) {
        TrepandoState* trepandoState = TrepandoState::getInstance();
        trepandoState->setDir(up, down);
        return trepandoState;
    }

    return ReposoState::getInstance();
}

void TrepandoState::perform() {
    this->velY = (this->up - this->down) * MARIO_VELOCIDAD;
}

void TrepandoState::update() {}

char TrepandoState::getEstado() {
    return TREPANDO;
}