#include "Collider.h"

const int HAMMER_USES = 3;

class HammerCollider {
public:
    void collide(Mario* mario, Barril* barril);
    void collide(Mario* mario, EnemigoFuego* enemigo);
private:
    int uses = HAMMER_USES;
    void decreaseUses(Mario* mario);
};