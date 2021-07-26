#pragma once
#include "Collider.h"

class NormalCollider: public Collider {
public:
    void collide(Mario* mario, Enemy* enemy);
    ColliderType getType();
};