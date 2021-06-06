#include "../Mario.hpp"
#include "ReposoState.h"
#include <string>

#include <stdio.h>
#include <iostream>

ReposoState::ReposoState() {
    std::cout << "CREANDO ReposoState " << std::endl;
}

void ReposoState::handleInput(char controls) {
    std::cout << "ReposoState: Atendiendo input -> " << controls << std::endl;
}

void ReposoState::update() {  
}