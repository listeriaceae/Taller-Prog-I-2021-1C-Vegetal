#pragma once
#include "Collider.h"

const int HAMMER_USES = 3;

class HammerCollider: public Collider {
public:
    void collide(Mario* mario, Enemy* enemy);
    ColliderType getType();
private:
    int uses = HAMMER_USES;
    void decreaseUses(Mario* mario);
    
};