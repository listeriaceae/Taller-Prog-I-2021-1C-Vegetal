#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Nivel2.h"
#include "Peach.h"
#include "DonkeyKong.h"
#include "Fuego.h"
#include "FireBarrel.h"


const char * BACKGROUND_IMAGE = "res/level2.bmp";

using namespace std;

Nivel2::Nivel2 (SDL_Renderer* window_renderer) {
    this->tickLastBarrel = 0;
    this->renderer = window_renderer;
    this->loadBackground();
    this->loadElements();
}

void Nivel2::loadBackground () {
    this->background_surface = SDL_LoadBMP(BACKGROUND_IMAGE);
    this->background_texture = SDL_CreateTextureFromSurface(this->renderer, this->background_surface);
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
}

void Nivel2::updateBackground () {
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
}

void Nivel2::loadElements () {
    Peach* girl = new Peach(314, 76, 40, 55);
    this->elements.push_front(girl);

    DonkeyKong* donkey = new DonkeyKong(129, 115, 100, 82);
    this->elements.push_front(donkey);

    Fuego* fire = new Fuego(10, 530, 30, 30);
    this->elements.push_front(fire);

    FireBarrel* barrel = new FireBarrel(10, 560, 30, 30);
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

void Nivel2::updateView () {
    
    if (SDL_GetTicks() - this->tickLastBarrel > 1500) {
        this->tickLastBarrel = SDL_GetTicks();
        this->addBarrel();
    }

    this->updateBackground();
    this->updateElements();
    this->updateBarrels();
}