#ifndef ENEMY_H
#define ENEMY_H

#include <cstdint>
#include "Entidad.hpp"

class Enemy : public Entidad
{
public:
  Enemy(punto32_t pos_, std::uint8_t points_) : Entidad{ pos_ }, points{ points_ } {}
  std::uint8_t getPoints() const { return points; }

private:
  std::uint8_t points;
};

#endif// ENEMY_H
