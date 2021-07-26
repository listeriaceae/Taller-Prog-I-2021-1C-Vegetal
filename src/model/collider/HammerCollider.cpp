#include "HammerCollider.h"
#include "NormalCollider.h"
#include "../Mario.hpp"

void HammerCollider::collide(Mario* mario, Enemy* enemy) {
    const bool collidedWithHammer = ((mario->direccion == DERECHA) && (mario->pos.x < enemy->pos.x))
                               || ((mario->direccion == IZQUIERDA) && (mario->pos.x > enemy->pos.x));

    if(collidedWithHammer && mario->estado <= CORRIENDO) {
        enemy->isEnabled = false;
        mario->audioObserver.update(ENEMY_DEATH);
        decreaseUses(mario);
        mario->addPoints(enemy->getPoints());
    }
    else {
        mario->die();
    }
}

void HammerCollider::decreaseUses(Mario* mario) {
    if (--uses == 0) {
        delete (mario->collider);
        mario->collider = new NormalCollider();
    }
}

ColliderType HammerCollider::getType() {
    return HAMMER;
}
