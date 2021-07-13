#include "Collider.h"

class TestCollider: public Collider {
public:
    void collide(Mario* mario, Barril* barril);
    void collide(Mario* mario, EnemigoFuego* enemigo);
};