#include "HammerCollider.h"
#include "NormalCollider.h"
#include "../Mario.hpp"


HammerCollider::HammerCollider() { }

void HammerCollider::collide(Mario* mario, Barril* barril) {
    printf("mario pos %f, barril pos %f \n", mario->pos.x, barril->pos.x);
    /*
    if(((mario->direccion == DERECHA) && (mario->pos.x > enemigo.pos.x))
    || ((mario->direccion == IZQUIERDA) && (mario->pos.x < enemigo.pos.x))) {
        mario->die();
    }
    else {
        barril->break();
        decreaseUses(mario);
    }
    */
}

void HammerCollider::collide(Mario* mario, EnemigoFuego* enemigo) {
    printf("mario pos %f, barril pos %f \n", mario->pos.x, enemigo->pos.x);
    //TODO: Agregar a mario la direccion a donde esta mirando
    /*
    if(((mario->direccion == DERECHA) && (mario->pos.x > enemigo.pos.x))
    || ((mario->direccion == IZQUIERDA) && (mario->pos.x < enemigo.pos.x))) {
        mario->die();
    }
    else {
        enemigo->die();
        decreaseUses(mario);
    }
    */
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