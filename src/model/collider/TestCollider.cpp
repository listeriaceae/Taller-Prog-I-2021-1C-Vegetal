#include "TestCollider.h"
#include "../../logger.h"
#include "../Mario.hpp"

void TestCollider::collide(Mario* , Barril* ) {
    logger::Logger::getInstance().logDebug("Collisión con barril");
}

void TestCollider::collide(Mario* , EnemigoFuego* ) {
    logger::Logger::getInstance().logDebug("Collisión con enemigo fuego");
}

ColliderType TestCollider::getType() {
    return TEST_MODE;
}