#pragma once
#include "../utils/marioStructs.h"
#include <SDL2/SDL_mixer.h>

namespace AudioController {
    void loadAudioFiles();
    void closeAudioFiles();

    void toggleMusic();
    void checkToggleMusicEvent();
    void playSounds(sounds_t sounds);
};