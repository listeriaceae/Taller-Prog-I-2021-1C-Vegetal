#ifndef MARIO_STRUCTS_H
#define MARIO_STRUCTS_H

#include <cstdint>
#include "punto.hpp"
#include "fixed_point.hpp"

enum SoundCode : std::uint8_t {
  JUMP = 1 << 0,
  DEATH = 1 << 1,
  FINISHED_LEVEL = 1 << 2,
  ITEM = 1 << 3,
  ENEMY_DEATH = 1 << 4
};

enum KeyCode : std::uint8_t {
  SPACE = 1 << 0,
  UP = 1 << 1,
  DOWN = 1 << 2,
  LEFT = 1 << 3,
  RIGHT = 1 << 4
};

enum class ColliderType : std::uint8_t { NORMAL, HAMMER };

enum class Estado : std::uint8_t {
  REPOSO,
  DE_ESPALDAS,
  CORRIENDO,
  SALTANDO,
  TREPANDO,
  MURIENDO,
  MUERTO,
  NIVEL_COMPLETO,
  GAME_OVER
};

enum class Direccion : std::uint8_t { IZQUIERDA, DERECHA };

struct PlayerState
{
  punto16_t pos;
  bool isEnabled;
  Estado estado;
  std::uint8_t sounds;
  ColliderType collider;
};

#endif// MARIO_STRUCTS_H
