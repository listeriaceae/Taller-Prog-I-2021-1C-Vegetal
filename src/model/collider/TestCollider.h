#pragma once
#include "Collider.h"

class TestCollider: public Collider {
public:
    void collide(Mario* mario, Enemy* enemy);
    ColliderType getType();
};