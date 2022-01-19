#ifndef HAMMER_COLLIDER_H
#define HAMMER_COLLIDER_H

#include "Collider.hpp"

class HammerCollider : public Collider
{
public:
  bool collide(Mario &mario, Enemy &enemy) const override;
  ColliderType getType() const override { return ColliderType::HAMMER; }
  inline static const HammerCollider *getInstance() { return &instance; }

private:
  constexpr HammerCollider() noexcept : Collider{} {}
  static const HammerCollider instance;
};

#endif// HAMMER_COLLIDER_H
