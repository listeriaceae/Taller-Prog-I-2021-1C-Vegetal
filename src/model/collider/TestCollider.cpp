#include "TestCollider.h"
#include "../../logger.h"

void collide(Mario* mario, Barril* barril) {
    logger::Logger::getInstance().logDebug("Collisión con barril");
}

void collide(Mario* mario, EnemigoFuego* enemigo) {
    logger::Logger::getInstance().logDebug("Collisión con enemigo fuego");
}
