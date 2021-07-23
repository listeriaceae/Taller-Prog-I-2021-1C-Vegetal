#include "TestCollider.h"
#include "../../logger.h"
#include "../Mario.hpp"

void TestCollider::collide(Mario* , Entidad* ) { }

ColliderType TestCollider::getType() {
    return TEST_MODE;
}