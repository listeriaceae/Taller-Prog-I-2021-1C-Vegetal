#include "TestCollider.h"

void TestCollider::collide(Mario* , Enemy* ) { }

ColliderType TestCollider::getType() {
    return TEST_MODE;
}