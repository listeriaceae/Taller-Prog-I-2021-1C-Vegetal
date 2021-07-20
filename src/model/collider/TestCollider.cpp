#include "TestCollider.h"
#include "../../logger.h"
#include "../Mario.hpp"

void TestCollider::collide(Mario* , Entidad* ) {
    logger::Logger::getInstance().logDebug("Collisión con entidad");
}

ColliderType TestCollider::getType() {
    return TEST_MODE;
}