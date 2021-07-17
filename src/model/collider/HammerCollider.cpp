#include "HammerCollider.h"
#include "NormalCollider.h"
#include "../Mario.hpp"


HammerCollider::HammerCollider() { }

void HammerCollider::collide(Mario* mario, Barril* barril) {
    if(((mario->direccion == DERECHA) && (mario->pos.x < barril->pos.x))
    || ((mario->direccion == IZQUIERDA) && (mario->pos.x > barril->pos.x))
    || ((mario->estado == DE_ESPALDAS || mario->estado == TREPANDO) && (mario->pos.y > barril->pos.y))) {
        barril->destroy();
        mario->audioObserver.update(ENEMY_DEATH);
        decreaseUses(mario);
    }
    else {
        mario->die();
    }
    
}

void HammerCollider::collide(Mario* mario, EnemigoFuego* enemigo) {
    if(((mario->direccion == DERECHA) && (mario->pos.x < enemigo->pos.x))
    || ((mario->direccion == IZQUIERDA) && (mario->pos.x > enemigo->pos.x))
    || ((mario->estado == DE_ESPALDAS || mario->estado == TREPANDO) && (mario->pos.y > enemigo->pos.y))) {
        enemigo->die();
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