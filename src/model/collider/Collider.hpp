#ifndef COLLIDER_H
#define COLLIDER_H

#include "../Enemy.hpp"
#include "../../utils/marioStructs.hpp"

class Mario;

class Collider
{
public:
  virtual ~Collider() = default;
  virtual bool collide(Mario &mario, Enemy &enemy) const = 0;
  virtual ColliderType getType() const = 0;

private:
};

#endif// COLLIDER_H
