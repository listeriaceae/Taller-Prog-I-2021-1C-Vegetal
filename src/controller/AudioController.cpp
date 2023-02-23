#include <SDL2/SDL_mixer.h>
#include <fmt/format.h>
#include <mutex>
#include "AudioController.hpp"
#include "../logger.hpp"
#include "../utils/marioStructs.hpp"

static const char music_file[] = "res/Audio/backgroundMusic.wav";
static const char jump_sound_file[] = "res/Audio/jump.wav";
static const char death_sound_file[] = "res/Audio/death.wav";
static const char finished_level_sound_file[] = "res/Audio/finishedLevel.wav";
static const char item_sound_file[] = "res/Audio/item.wav";
static const char enemy_death_sound_file[] = "res/Audio/enemyDeath.wav";

namespace AudioController {
static Mix_Music *music{ nullptr };
static Mix_Chunk *jumpSound{ nullptr };
static Mix_Chunk *deathSound{ nullptr };
static Mix_Chunk *finishedLevelSound{ nullptr };
static Mix_Chunk *itemSound{ nullptr };
static Mix_Chunk *enemyDeathSound{ nullptr };

void
loadAudioFiles()
{
  if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512)
      < 0)
    logger::logError("Mixer initialization error");

  music = Mix_LoadMUS(music_file);
  if (music == nullptr)
    logger::logError(
      fmt::format("Music file not found: '{}'", music_file));

  jumpSound = Mix_LoadWAV(jump_sound_file);
  if (jumpSound == nullptr)
    logger::logError(
      fmt::format("jump sound effect file not found: '{}'", jump_sound_file));

  deathSound = Mix_LoadWAV(death_sound_file);
  if (deathSound == nullptr)
    logger::logError(
      fmt::format("death sound effect file not found: '{}'", death_sound_file));

  finishedLevelSound = Mix_LoadWAV(finished_level_sound_file);
  if (finishedLevelSound == NULL)
    logger::logError(
      fmt::format("finished level sound effect file not found: '{}'",
                  finished_level_sound_file));
  else
    finishedLevelSound->volume = 40;
  itemSound = Mix_LoadWAV(item_sound_file);
  if (itemSound == nullptr)
    logger::logError(
      fmt::format("item sound effect file not found: '{}'", item_sound_file));

  enemyDeathSound = Mix_LoadWAV(enemy_death_sound_file);
  if (deathSound == nullptr)
    logger::logError(fmt::format(
      "enemy death sound effect file not found: '{}'", enemy_death_sound_file));
}

void
startMusic()
{
  static std::once_flag flag;
  std::call_once(flag, Mix_PlayMusic, music, -1);
}

static void
toggleMusic()
{
  if (Mix_PlayingMusic())
    if (Mix_PausedMusic())
      Mix_ResumeMusic();
    else
      Mix_PauseMusic();
  else
    startMusic();
}

void
checkToggleMusicEvent(int m_state)
{
  static bool isKeyDown = false;

  if (!isKeyDown && m_state)
    toggleMusic();
  isKeyDown = m_state;
}

void
playSounds(int sounds)
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

void
closeAudioFiles()
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
  jumpSound = deathSound = finishedLevelSound = itemSound = enemyDeathSound =
    nullptr;
  while (Mix_Init(0))
    Mix_Quit();
  Mix_CloseAudio();
}
}// namespace AudioController
