#include "NormalCollider.hpp"
#include "../Mario.hpp"

const NormalCollider NormalCollider::instance{};

bool NormalCollider::collide(Mario &mario, Enemy &) const
{
  mario.die();
  return false;
}
