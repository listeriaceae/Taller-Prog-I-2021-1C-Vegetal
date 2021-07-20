#pragma once
#include "Collider.h"

class NormalCollider: public Collider {
public:
    NormalCollider();
    void collide(Mario* mario, Entidad* entidad);
    ColliderType getType();
};