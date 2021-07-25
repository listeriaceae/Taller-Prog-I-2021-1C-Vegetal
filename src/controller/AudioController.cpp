#include <SDL2/SDL.h>
#include "AudioController.h"
#include "../logger.h"

const char* const MUSIC_FILE_NAME = "res/Audio/backgroundMusic.wav";
const char* const JUMP_SOUND_FILE = "res/Audio/jump.wav";
const char* const DEATH_SOUND_FILE = "res/Audio/death.wav";
const char* const FINISHED_LEVEL_SOUND_FILE = "res/Audio/finishedLevel.wav";
const char* const ITEM_SOUND_FILE = "res/Audio/item.wav";
const char* const ENEMY_DEATH_SOUND_FILE = "res/Audio/enemyDeath.wav";

namespace AudioController {
    bool isKeyDown = false;
    Mix_Music* music{nullptr};
    Mix_Chunk* jumpSound{nullptr};
    Mix_Chunk* deathSound{nullptr};
    Mix_Chunk* finishedLevelSound{nullptr};
    Mix_Chunk* itemSound{nullptr};
    Mix_Chunk* enemyDeathSound{nullptr};

    void loadAudioFiles() {
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512) < 0)
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
        
        finishedLevelSound = Mix_LoadWAV(FINISHED_LEVEL_SOUND_FILE);
        if(finishedLevelSound == NULL)
            logger::Logger::getInstance().logError("finished level sound effect file not found: " + (std::string)FINISHED_LEVEL_SOUND_FILE);
        else
            finishedLevelSound->volume = 48;
        itemSound = Mix_LoadWAV(ITEM_SOUND_FILE);
        if(itemSound == nullptr)
            logger::Logger::getInstance().logError("item sound effect file not found: " + (std::string)ITEM_SOUND_FILE);
        
        enemyDeathSound = Mix_LoadWAV(ENEMY_DEATH_SOUND_FILE);
        if(deathSound == nullptr)
            logger::Logger::getInstance().logError("enemy death sound effect file not found: " + (std::string)ENEMY_DEATH_SOUND_FILE);
    }

    void toggleMusic() {
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

    void checkToggleMusicEvent() {
        const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
        if (!isKeyDown) {
            if (keyboard[SDL_SCANCODE_M]) {
                isKeyDown = true;
                toggleMusic();
            }
        }
        else {
            if (!keyboard[SDL_SCANCODE_M]) {
                isKeyDown = false;
            }
        }
    }

    void playSounds(sounds_t sounds) {
        if(sounds.jump) {
            Mix_PlayChannel(-1, jumpSound, 0);
        }

        if(sounds.death) {
            Mix_PlayChannel(-1, deathSound, 0);
        }

        if(sounds.finishedLevel) {
            Mix_PlayChannel(-1, finishedLevelSound, 0);
        }

        if(sounds.item) {
            Mix_PlayChannel(-1, itemSound, 0);
        }

        if(sounds.enemyDeath) {
            Mix_PlayChannel(-1, enemyDeathSound, 0);
        }
    }

    void closeAudioFiles() {
        Mix_FreeMusic(music);
        Mix_FreeChunk(jumpSound);
        Mix_FreeChunk(deathSound);
        Mix_FreeChunk(finishedLevelSound);
        Mix_FreeChunk(itemSound);
        Mix_FreeChunk(enemyDeathSound);
        while (Mix_Init(0)) {
            Mix_Quit();
        }
        Mix_CloseAudio();
    }
}