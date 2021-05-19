#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "level2.h"
#include "Peach.h"
#include "DonkeyKong.h"
#include "Fuego.h"
#include "FireBarrel.h"


const char * BACKGROUND_IMAGE = "level2.bmp";

using namespace std;

Level2::Level2 (SDL_Renderer* window_renderer) {
    this->tickLastBarrel = 0;
    this->renderer = window_renderer;
    this->loadBackground();
    this->loadComponents();
}

void Level2::loadBackground () {
    this-> background_surface = SDL_LoadBMP(BACKGROUND_IMAGE);
    this->background_texture = SDL_CreateTextureFromSurface(this->renderer, background_surface);
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void Level2::updateBackground () {
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, NULL);
}

void Level2::loadComponents () {
    Peach* girl = new Peach(314, 76, 40, 55);
    this->components.push_front(girl);

    DonkeyKong* donkey = new DonkeyKong(129, 115, 100, 82);
    this->components.push_front(donkey);

    Fuego* fire = new Fuego(50, 530, 30, 30);
    this->components.push_front(fire);

    FireBarrel* barrel = new FireBarrel(50, 560, 30, 30);
    this->components.push_front(barrel);
}

void Level2::updateComponents () {
    list<Entidad*>::iterator it;
    for (it = this->components.begin(); it != this->components.end(); ++it){
        (*it)->mostrar(this->renderer);
    }
}


void Level2::addBarrel () {
    int posX = rand() % 750 + 10;
    this->barrels.push_back(Barril(posX, 150, 0, 10));
}

void Level2::updateBarrels () {
    for (int i = 0; i < this->barrels.size(); i++) {
        try {
            this->barrels.at(i).mover();
            this->barrels.at(i).mostrar(this->renderer);
        }
        catch (int e) {
            this->barrels.erase(this->barrels.begin()+i);
        }
    } 
}

void Level2::updateView () {
    
    if (SDL_GetTicks() - this->tickLastBarrel > 1500) {
        this->tickLastBarrel = SDL_GetTicks();
        this->addBarrel();
    }

    SDL_RenderClear(this->renderer);
    this->updateBackground();
    this->updateComponents();
    this->updateBarrels();

    SDL_RenderPresent(this->renderer);
}