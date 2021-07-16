#pragma once
#include "../Barril.h"
#include "../EnemigoFuego.h"
#include "../../utils/Constants.hpp"

class Mario;

class Collider {
public:
    virtual ~Collider() = default;
    virtual void collide(Mario* mario, Barril* barril) = 0;
    virtual void collide(Mario* mario, EnemigoFuego* enemigo) = 0;
    virtual ColliderType getType() = 0;
private:
};