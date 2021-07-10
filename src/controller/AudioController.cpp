#include <SDL2/SDL.h>
#include "AudioController.h"
#include "../logger.h"

bool AudioController::isKeyDown = false;
Mix_Music* AudioController::music = NULL;
Mix_Chunk* AudioController::jumpSound = NULL;
Mix_Chunk* AudioController::deathSound = NULL;

const char* const MUSIC_FILE_NAME = "res/Audio/backgroundMusic.wav";
const char* const JUMP_SOUND_FILE = "res/Audio/jump.wav";
const char* const DEATH_SOUND_FILE = "res/Audio/death.wav";

const char JUMP_SOUND_CODE = 1;
const char DEATH_SOUND_CODE = 2;

void AudioController::loadAudioFiles() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0)
        logger::Logger::getInstance().logError("Mixer initialization error");

    music = Mix_LoadMUS(MUSIC_FILE_NAME);
    if(music == NULL) 
        logger::Logger::getInstance().logError("Music file not found: " + (std::string)MUSIC_FILE_NAME);
    
    jumpSound = Mix_LoadWAV(JUMP_SOUND_FILE);
    if(jumpSound == NULL)
        logger::Logger::getInstance().logError("jump sound effect file not found: " + (std::string)JUMP_SOUND_FILE);

    deathSound = Mix_LoadWAV(DEATH_SOUND_FILE);
    if(deathSound == NULL)
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
    if(!isKeyDown) {
        if(keyboard[SDL_SCANCODE_M]) {
            isKeyDown = true;
            AudioController::toggleMusic();
        }
    }
    else {
        if(!keyboard[SDL_SCANCODE_M]) {
            isKeyDown = false;
        }
    }
}

void AudioController::playSounds(char sounds) {
    if(sounds & JUMP_SOUND_CODE) {
        Mix_PlayChannel(-1, jumpSound, 0);
        printf("salto\n");
    }

    if(sounds & DEATH_SOUND_CODE) {
        Mix_PlayChannel(-1, deathSound, 0);
        printf("muerte\n");
    }
}

void AudioController::closeAudioFiles() {
    Mix_FreeMusic(music);
    music = NULL;
}