#include "NormalCollider.h"
#include "../Mario.hpp"

NormalCollider::NormalCollider() { }

void NormalCollider::collide(Mario* mario, Entidad* ) {
    mario->die();
}

ColliderType NormalCollider::getType() {
    return NORMAL;
}