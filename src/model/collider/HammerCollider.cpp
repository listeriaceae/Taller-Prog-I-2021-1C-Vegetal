#include "HammerCollider.h"
#include "NormalCollider.h"

void HammerCollider::collide(Mario* mario, Barril* barril) {
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
    /*if(uses <= 0) {
        mario->collider = new NormalCollider();
    }*/
}