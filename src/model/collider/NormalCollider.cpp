#include "NormalCollider.h"

void NormalCollider::collide(Mario* mario, Barril* barril) {
    mario->die();
}

void NormalCollider::collide(Mario* mario, EnemigoFuego* enemigo) {
    mario->die();
}