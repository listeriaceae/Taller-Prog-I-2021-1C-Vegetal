#include "NormalCollider.h"
#include "../Mario.hpp"

NormalCollider::NormalCollider() { }

void NormalCollider::collide(Mario* mario, Barril* ) {
    mario->die();
}

void NormalCollider::collide(Mario* mario, EnemigoFuego* ) {
    mario->die();
}

ColliderType NormalCollider::getType() {
    return NORMAL;
}