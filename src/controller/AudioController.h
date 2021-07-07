#pragma once
#include <SDL2/SDL_mixer.h>

class AudioController {
public:
    static void loadAudioFiles();
    static void closeAudioFiles();

    static void toggleMusic();
    static void checkToggleMusicEvent();
private:
    static Mix_Music *music;
    static bool isKeyDown;
};