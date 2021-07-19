#include "HammerCollider.h"
#include "NormalCollider.h"
#include "../Mario.hpp"


HammerCollider::HammerCollider() { }

void HammerCollider::collide(Mario* mario, Barril* barril) {
    bool collidedWithHammer = ((mario->direccion == DERECHA) && (mario->pos.x < barril->pos.x))
    || ((mario->direccion == IZQUIERDA) && (mario->pos.x > barril->pos.x));
    bool collidedOnLadder = ((mario->estado == DE_ESPALDAS || mario->estado == TREPANDO) && (mario->pos.y > barril->pos.y));

    if(collidedWithHammer || collidedOnLadder) {
        barril->isDisabled = true;
        mario->audioObserver.update(ENEMY_DEATH);
        decreaseUses(mario);
    }
    else {
        mario->die();
    }
    
}

void HammerCollider::collide(Mario* mario, EnemigoFuego* enemigo) {
    bool collidedWithHammer = ((mario->direccion == DERECHA) && (mario->pos.x < enemigo->pos.x))
    || ((mario->direccion == IZQUIERDA) && (mario->pos.x > enemigo->pos.x));
    bool collidedOnLadder = ((mario->estado == DE_ESPALDAS || mario->estado == TREPANDO) && (mario->pos.y > enemigo->pos.y));
    
    if(collidedWithHammer || collidedOnLadder) {
        enemigo->isDisabled = true;
        mario->audioObserver.update(ENEMY_DEATH);
        decreaseUses(mario);
    }
    else {
        mario->die();
    }
    
}

void HammerCollider::decreaseUses(Mario* mario) {
    this->uses--;
    if(uses <= 0) {
        delete (mario->collider);
        mario->collider = new NormalCollider();
    }
}

ColliderType HammerCollider::getType() {
    return HAMMER;
}