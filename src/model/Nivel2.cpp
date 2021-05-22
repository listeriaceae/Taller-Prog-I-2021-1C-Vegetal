#include <iostream>
#include <stdlib.h>
#include <string>
#include "Nivel2.h"
#include "Peach.h"
#include "DonkeyKong.h"
#include "Fuego.h"
#include "FireBarrel.h"
#include "../utils/ Constants.hpp"

using namespace std;

Nivel2::Nivel2 (SDL_Renderer* renderer) {
    this->tickLastBarrel = 0;
    this->renderer = renderer;
}

void Nivel2::loadBackground () {
    this->background_surface = IMG_Load(backgroundImage.c_str());
    if(this->background_surface == NULL) {
        this->background_surface = IMG_Load(DEFAULT_IMAGE.c_str());
    }
    this->background_texture = SDL_CreateTextureFromSurface(this->renderer, this->background_surface);
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
}

void Nivel2::updateBackground () {
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
}

void Nivel2::loadElements () {
    Peach* girl = new Peach(renderer);
    this->elements.push_front(girl);

    DonkeyKong* donkey = new DonkeyKong(renderer);
    this->elements.push_front(donkey);

    Fuego* fire = new Fuego(N2_POSX_FUEGO, N2_POSY_FUEGO, 0.5, renderer);
    this->elements.push_front(fire);

    FireBarrel* barrel = new FireBarrel(renderer);
    this->elements.push_front(barrel);
}

void Nivel2::addElement (Entidad* element) {
    this->elements.push_front(element);
}

void Nivel2::updateElements () {
    list<Entidad*>::iterator it;
    for (it = this->elements.begin(); it != this->elements.end(); ++it){
        (*it)->mover();
        (*it)->mostrar(this->renderer);
    }
}


void Nivel2::addBarrel () {
    int posX = rand() % 750 + 10;
    this->barrels.push_back(Barril(posX, 150, 0, 10));
}

void Nivel2::updateBarrels () {
    for (uint i = 0; i < this->barrels.size(); i++) {
        try {
            this->barrels.at(i).mover();
            this->barrels.at(i).mostrar(this->renderer);
        }
        catch (exception& e) {
            this->barrels.erase(this->barrels.begin()+i);
        }
    } 
}
void Nivel2::initialize() {
    this->loadBackground();
    this->loadElements();
}

void Nivel2::updateView () {
    
    if (SDL_GetTicks() - this->tickLastBarrel > 1500) {
        this->tickLastBarrel = SDL_GetTicks();
        this->addBarrel();
    }

    this->updateBackground();
    this->updateElements();
    this->updateBarrels();
}
void Nivel2::setBackground(std::string background) {
    this->backgroundImage = background;
}
