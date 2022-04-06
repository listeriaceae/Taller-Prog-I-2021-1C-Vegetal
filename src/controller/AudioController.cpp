#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <fmt/format.h>
#include "AudioController.hpp"
#include "../logger.hpp"
#include "../utils/marioStructs.hpp"

static const char MUSIC_FILE_NAME[] = "res/Audio/backgroundMusic.wav";
static const char JUMP_SOUND_FILE[] = "res/Audio/jump.wav";
static const char DEATH_SOUND_FILE[] = "res/Audio/death.wav";
static const char FINISHED_LEVEL_SOUND_FILE[] = "res/Audio/finishedLevel.wav";
static const char ITEM_SOUND_FILE[] = "res/Audio/item.wav";
static const char ENEMY_DEATH_SOUND_FILE[] = "res/Audio/enemyDeath.wav";

namespace AudioController {
static bool isKeyDown = false;
static Mix_Music *music{ nullptr };
static Mix_Chunk *jumpSound{ nullptr };
static Mix_Chunk *deathSound{ nullptr };
static Mix_Chunk *finishedLevelSound{ nullptr };
static Mix_Chunk *itemSound{ nullptr };
static Mix_Chunk *enemyDeathSound{ nullptr };

void loadAudioFiles()
{
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512) < 0)
    logger::Logger::getInstance().logError("Mixer initialization error");

  music = Mix_LoadMUS(MUSIC_FILE_NAME);
  if (music == nullptr)
    logger::Logger::getInstance().logError(
      fmt::format("Music file not found: '{}'", MUSIC_FILE_NAME));

  jumpSound = Mix_LoadWAV(JUMP_SOUND_FILE);
  if (jumpSound == nullptr)
    logger::Logger::getInstance().logError(
      fmt::format("jump sound effect file not found: '{}'", JUMP_SOUND_FILE));

  deathSound = Mix_LoadWAV(DEATH_SOUND_FILE);
  if (deathSound == nullptr)
    logger::Logger::getInstance().logError(
      fmt::format("death sound effect file not found: '{}'",
        DEATH_SOUND_FILE));

  finishedLevelSound = Mix_LoadWAV(FINISHED_LEVEL_SOUND_FILE);
  if (finishedLevelSound == NULL)
    logger::Logger::getInstance().logError(
      fmt::format("finished level sound effect file not found: '{}'",
        FINISHED_LEVEL_SOUND_FILE));
  else
    finishedLevelSound->volume = 40;
  itemSound = Mix_LoadWAV(ITEM_SOUND_FILE);
  if (itemSound == nullptr)
    logger::Logger::getInstance().logError(
      fmt::format("item sound effect file not found: '{}'", ITEM_SOUND_FILE));

  enemyDeathSound = Mix_LoadWAV(ENEMY_DEATH_SOUND_FILE);
  if (deathSound == nullptr)
    logger::Logger::getInstance().logError(
      fmt::format("enemy death sound effect file not found: '{}'",
        ENEMY_DEATH_SOUND_FILE));
}

void toggleMusic()
{
  if (Mix_PlayingMusic() == 0) {
    Mix_PlayMusic(music, -1);
  } else {
    if (Mix_PausedMusic() == 1) {
      Mix_ResumeMusic();
    } else {
      Mix_PauseMusic();
    }
  }
}

void checkToggleMusicEvent()
{
  const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
  if (!isKeyDown) {
    if (keyboard[SDL_SCANCODE_M]) {
      isKeyDown = true;
      toggleMusic();
    }
  } else if (!keyboard[SDL_SCANCODE_M])
      isKeyDown = false;
}

void playSounds(unsigned char sounds)
{
  if (sounds == 0)
    return;

  if (sounds & JUMP)
    Mix_PlayChannel(-1, jumpSound, 0);
  if (sounds & DEATH)
    Mix_PlayChannel(-1, deathSound, 0);
  if (sounds & FINISHED_LEVEL)
    Mix_PlayChannel(-1, finishedLevelSound, 0);
  if (sounds & ITEM)
    Mix_PlayChannel(-1, itemSound, 0);
  if (sounds & ENEMY_DEATH)
    Mix_PlayChannel(-1, enemyDeathSound, 0);
}

void closeAudioFiles()
{
  if (music != nullptr)
    Mix_FreeMusic(music);
  if (jumpSound != nullptr)
    Mix_FreeChunk(jumpSound);
  if (deathSound != nullptr)
    Mix_FreeChunk(deathSound);
  if (finishedLevelSound != nullptr)
    Mix_FreeChunk(finishedLevelSound);
  if (itemSound != nullptr)
    Mix_FreeChunk(itemSound);
  if (enemyDeathSound != nullptr)
    Mix_FreeChunk(enemyDeathSound);
  music = nullptr;
  jumpSound = deathSound = finishedLevelSound = itemSound = enemyDeathSound = nullptr;
  while (Mix_Init(0))
    Mix_Quit();
  Mix_CloseAudio();
}
}// namespace AudioController
