#include "TestCollider.h"
#include "../../logger.h"

void TestCollider::collide(Mario* mario, Barril* barril) {
    logger::Logger::getInstance().logDebug("Collisión con barril");
}

void TestCollider::collide(Mario* mario, EnemigoFuego* enemigo) {
    logger::Logger::getInstance().logDebug("Collisión con enemigo fuego");
}
