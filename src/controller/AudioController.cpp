#include <SDL2/SDL.h>
#include "AudioController.h"
#include "../logger.h"

bool AudioController::isKeyDown = false;
Mix_Music* AudioController::music{nullptr};

const char *const MUSIC_FILE_NAME = "res/Audio/backgroundMusic.wav";

void AudioController::loadAudioFiles() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        logger::Logger::getInstance().logError("Mixer initialization error");

    music = Mix_LoadMUS(MUSIC_FILE_NAME);
    if(music == nullptr)
        logger::Logger::getInstance().logError("Music file not found: " + (std::string)MUSIC_FILE_NAME);
}

void AudioController::toggleMusic() {
    if(Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1);
    } 
    else {
        if(Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        }
        else {
            Mix_PauseMusic();
        }
    }
}

void AudioController::checkToggleMusicEvent() {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
    if (!isKeyDown) {
        if (keyboard[SDL_SCANCODE_M]) {
            isKeyDown = true;
            AudioController::toggleMusic();
        }
    }
    else {
        if (!keyboard[SDL_SCANCODE_M]) {
            isKeyDown = false;
        }
    }
}
void AudioController::closeAudioFiles() {
    Mix_FreeMusic(music);
    music = nullptr;
}