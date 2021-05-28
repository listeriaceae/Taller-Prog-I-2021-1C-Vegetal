#include "MarioController.h"
#include "../logger.h"

MarioController::MarioController(Mario *mario) {
    this->mario = mario;
}

void MarioController::update() {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
    char controls = 0;
    controls |= keyboard[SDL_SCANCODE_SPACE] * SPACE;
    controls |= keyboard[SDL_SCANCODE_UP] * UP;
    controls |= keyboard[SDL_SCANCODE_DOWN] * DOWN;
    controls |= keyboard[SDL_SCANCODE_LEFT] * LEFT;
    controls |= keyboard[SDL_SCANCODE_RIGHT] * RIGHT;

    mario->setEstado(controls);
}