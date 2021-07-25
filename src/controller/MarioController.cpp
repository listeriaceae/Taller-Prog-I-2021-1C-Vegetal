#include <SDL2/SDL.h>
#include "MarioController.h"
#include "../logger.h"

const char *const MSG_TOGGLE_TEST = "Toggled test mode.";

bool isKeyUp = true;

unsigned char getTestModeKeyState(const Uint8 *keyboard) {
    if(isKeyUp && keyboard[SDL_SCANCODE_T]) {
        logger::Logger::getInstance().logDebug(MSG_TOGGLE_TEST);
        puts(MSG_TOGGLE_TEST);
        isKeyUp = false;
        return 1;
    } else if(!keyboard[SDL_SCANCODE_T]){
        isKeyUp = true;
    }
    return 0;
}

namespace MarioController {
    controls_t getControls() {
        const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

        return controls_t{keyboard[SDL_SCANCODE_SPACE],
                        keyboard[SDL_SCANCODE_UP],
                        keyboard[SDL_SCANCODE_DOWN],
                        keyboard[SDL_SCANCODE_LEFT],
                        keyboard[SDL_SCANCODE_RIGHT],
                        getTestModeKeyState(keyboard)  
                        };
    }
}