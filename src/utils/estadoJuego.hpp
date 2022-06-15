#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <array>
#include <variant>
#include "punto.hpp"
#include "marioStructs.hpp"
#include "Constants.hpp"

struct PlayerInfo
{
  char name[4];
  std::int8_t lives;
  std::uint8_t score;
};

struct lv1
{
  std::array<punto16_t, MAX_PLATFORMS> platforms;
  std::array<punto16_t, MAX_ENEMIES> enemies;
};

using lv2 = std::array<punto16_t, MAX_BARRELS>;

struct LevelState
{
  std::array<punto16_t, MAX_HAMMERS> hammers;
  std::array<PlayerState, MAX_PLAYERS> players;
  std::variant<std::monostate, lv1, lv2, bool> v;
};

struct GameState
{
  std::array<PlayerInfo, MAX_PLAYERS> players;
  LevelState level;
};

#endif// GAME_STATE_H
