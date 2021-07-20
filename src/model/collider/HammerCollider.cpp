#include "HammerCollider.h"
#include "NormalCollider.h"
#include "../Mario.hpp"


HammerCollider::HammerCollider() { }

void HammerCollider::collide(Mario* mario, Entidad* entidad) {
    bool collidedWithHammer = ((mario->direccion == DERECHA) && (mario->pos.x < entidad->pos.x))
    || ((mario->direccion == IZQUIERDA) && (mario->pos.x > entidad->pos.x));
    bool collidedOnLadder = ((mario->estado == DE_ESPALDAS || mario->estado == TREPANDO) && (mario->pos.y > entidad->pos.y));

    if(collidedWithHammer || collidedOnLadder) {
        entidad->isEnabled = false;
        mario->audioObserver.update(ENEMY_DEATH);
        decreaseUses(mario);
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
