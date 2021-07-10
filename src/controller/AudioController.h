#pragma once
#include <SDL2/SDL_mixer.h>

class AudioController {
public:
    static void loadAudioFiles();
    static void closeAudioFiles();

    static void toggleMusic();
    static void checkToggleMusicEvent();
    static void playSounds(char sounds);
private:
    static Mix_Music* music;
    static Mix_Chunk* jumpSound;
    static Mix_Chunk* deathSound;
    static bool isKeyDown;
};