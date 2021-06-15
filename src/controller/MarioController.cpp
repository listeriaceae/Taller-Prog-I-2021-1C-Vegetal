#include <SDL2/SDL.h>
#include "MarioController.h"


char MarioController::getControls() {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
    controls_t controls;
    controls.space = keyboard[SDL_SCANCODE_SPACE];
    controls.up = keyboard[SDL_SCANCODE_UP];
    controls.down = keyboard[SDL_SCANCODE_DOWN];
    controls.left = keyboard[SDL_SCANCODE_LEFT];
    controls.right = keyboard[SDL_SCANCODE_RIGHT];

    //mario->setEstado(controls);
    return controls;
}