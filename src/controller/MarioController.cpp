#include "MarioController.h"
#include "../logger.h"

MarioController::MarioController(Mario *mario) {
    this->mario = mario;
}

void MarioController::handleEvent(SDL_Event *e) {
    // If a key was pressed
    if(e->type == SDL_KEYDOWN && e->key.repeat == 0) {

        int key = e->key.keysym.sym;

        if (key == SDLK_SPACE) {
            mario->saltar();
            return;
        }
        if (key < SDLK_RIGHT || key > SDLK_UP) {
            logger::Logger::getInstance().logDebug("Unknown key pressed");
            return;
        }
        up |= (key == SDLK_UP);
        down |= (key == SDLK_DOWN);
        left |= (key == SDLK_LEFT);
        right |= (key == SDLK_RIGHT);
    }
    // If a key was released
    else if( e->type == SDL_KEYUP && e->key.repeat == 0 ) {

        int key = e->key.keysym.sym;

        if (key < SDLK_RIGHT || key > SDLK_UP) return;
        up &= (key != SDLK_UP);
        down &= (key != SDLK_DOWN);
        left &= (key != SDLK_LEFT);
        right &= (key != SDLK_RIGHT);
    } else return;
    mario->setEstado(up, down, left, right);
}