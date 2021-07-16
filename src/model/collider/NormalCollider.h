#pragma once
#include "Collider.h"

class NormalCollider: public Collider {
public:
    NormalCollider();
    void collide(Mario* mario, Barril* barril);
    void collide(Mario* mario, EnemigoFuego* enemigo);
    ColliderType getType();
};