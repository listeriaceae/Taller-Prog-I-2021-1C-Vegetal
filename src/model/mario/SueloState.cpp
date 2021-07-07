#include "SueloState.h"
#include "AireState.h"
#include "TrepandoState.h"
#include "../../utils/Constants.hpp"

SueloState *SueloState::instance{nullptr};

SueloState::SueloState() {}

SueloState *SueloState::getInstance() {
    if (instance == nullptr) {
        instance = new SueloState();
    }
    return instance;
}

MarioState *SueloState::update(float &x, float &y, float &xSpeed, float &ySpeed, char &estado, const controls_t controls) {
    const Ladder *ladder = stage->getLadder(x, y, controls.up - controls.down);
    if (ladder != nullptr) {
        float distance = ladder->getX() - x;
        if (-4 <= distance && distance <= 4) {
            x = ladder->getX();
            TrepandoState *trepandoState = TrepandoState::getInstance();
            trepandoState->setLimits(ladder->getBottom(), ladder->getTop());
            return trepandoState;
        }
    }
    xSpeed = (controls.right - controls.left) * MARIO_VEL_X;
    ySpeed = GRAVEDAD;
    x += xSpeed * ((x < ANCHO_NIVEL - ANCHO_MARIO && 0 < xSpeed) || (0 < x && xSpeed < 0));
    y -= ySpeed;
    if (controls.space || !stage->collide(x, y, xSpeed, ySpeed)) {
        xSpeed *= controls.space;
        ySpeed = controls.space * MARIO_VEL_SALTO;
        return AireState::getInstance();
    }
    estado = (estado == DE_ESPALDAS) + (xSpeed != 0) * (CORRIENDO - (estado == DE_ESPALDAS));
    return instance;
}