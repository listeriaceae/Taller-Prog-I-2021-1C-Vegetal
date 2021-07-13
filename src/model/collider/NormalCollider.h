#include "Collider.h"

class NormalCollider: public Collider {
public:
    void collide(Mario* mario, Barril* barril);
    void collide(Mario* mario, EnemigoFuego* enemigo);
};