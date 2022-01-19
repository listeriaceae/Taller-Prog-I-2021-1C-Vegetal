#include "HammerCollider.hpp"
#include "NormalCollider.hpp"
#include "../Mario.hpp"

const HammerCollider HammerCollider::instance{};

bool HammerCollider::collide(Mario &mario, Enemy &enemy) const
{
  const bool collidedWithHammer =
    ((mario.direccion == Direccion::DERECHA) && (mario.pos.x < enemy.pos.x)) || ((mario.direccion == Direccion::IZQUIERDA) && (mario.pos.x >= enemy.pos.x));

  if (collidedWithHammer && mario.estado <= Estado::CORRIENDO) {
    mario.audioObserver.update(ENEMY_DEATH);
    if (--mario.hammerUses == 0)
      mario.collider = NormalCollider::getInstance();
    mario.score += enemy.getPoints();
    return true;
  } else {
    mario.die();
    return false;
  }
}
