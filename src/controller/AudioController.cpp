#include <SDL2/SDL.h>
#include "AudioController.h"
#include "../logger.h"

bool AudioController::isKeyDown = false;
Mix_Music* AudioController::music{nullptr};
Mix_Chunk* AudioController::jumpSound{nullptr};
Mix_Chunk* AudioController::deathSound{nullptr};

const char* const MUSIC_FILE_NAME = "res/Audio/backgroundMusic.wav";
const char* const JUMP_SOUND_FILE = "res/Audio/jump.wav";
const char* const DEATH_SOUND_FILE = "res/Audio/death.wav";

void AudioController::loadAudioFiles() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0)
        logger::Logger::getInstance().logError("Mixer initialization error");

    music = Mix_LoadMUS(MUSIC_FILE_NAME);
    if(music == nullptr)
        logger::Logger::getInstance().logError("Music file not found: " + (std::string)MUSIC_FILE_NAME);
    
    jumpSound = Mix_LoadWAV(JUMP_SOUND_FILE);
    if(jumpSound == nullptr)
        logger::Logger::getInstance().logError("jump sound effect file not found: " + (std::string)JUMP_SOUND_FILE);

    deathSound = Mix_LoadWAV(DEATH_SOUND_FILE);
    if(deathSound == nullptr)
        logger::Logger::getInstance().logError("death sound effect file not found: " + (std::string)DEATH_SOUND_FILE);
    

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

void AudioController::playSounds(sounds_t sounds) {
    if(sounds.jump) {
        Mix_PlayChannel(-1, jumpSound, 0);
    }

    if(sounds.death) {
        Mix_PlayChannel(-1, deathSound, 0);
    }
}

void AudioController::closeAudioFiles() {
    Mix_FreeMusic(music);
    music = nullptr;
}