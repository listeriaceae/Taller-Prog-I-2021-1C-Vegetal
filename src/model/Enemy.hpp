#ifndef ENEMY_H
#define ENEMY_H

#include "../utils/punto.hpp"

class Enemy
{
public:
  Enemy(punto32_t pos_, std::uint8_t points_) : pos{ pos_ }, points{ points_ } {}
  std::uint8_t getPoints() const { return points; }

  punto32_t pos;
  bool isEnabled = true;
  std::uint8_t points;
};

#endif// ENEMY_H
