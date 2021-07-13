#pragma once
#include "../Mario.hpp"
#include "../Barril.h"
#include "../EnemigoFuego.h"

class Collider {
    virtual void collide(Mario* mario, Barril* barril) = 0;
    virtual void collide(Mario* mario, EnemigoFuego* enemigo) = 0;
    virtual ~Collider() = default;
};