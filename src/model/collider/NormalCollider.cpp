#include "NormalCollider.h"
#include "../Mario.hpp"

void NormalCollider::collide(Mario* mario, Enemy* ) {
    mario->die();
}

ColliderType NormalCollider::getType() {
    return NORMAL;
}