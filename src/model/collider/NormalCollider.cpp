#include "NormalCollider.h"

void collide(Mario* mario, Barril* barril) {
    mario->die();
}

void collide(Mario* mario, EnemigoFuego* enemigo) {
    mario->die();
}