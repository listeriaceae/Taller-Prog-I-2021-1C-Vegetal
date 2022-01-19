#ifndef NORMAL_COLLIDER_H
#define NORMAL_COLLIDER_H

#include "Collider.hpp"

class NormalCollider : public Collider
{
public:
  bool collide(Mario &mario, Enemy &enemy) const override;
  ColliderType getType() const override { return ColliderType::NORMAL; }
  inline static const NormalCollider *getInstance() { return &instance; }

private:
  constexpr NormalCollider() noexcept : Collider{} {};
  static const NormalCollider instance;
};

#endif// NORMAL_COLLIDER_H
