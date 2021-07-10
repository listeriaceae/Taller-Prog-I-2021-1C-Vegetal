#include "SueloState.h"
#include "AireState.h"
#include "TrepandoState.h"
#include "../../utils/Constants.hpp"

SueloState *SueloState::instance = NULL;

SueloState::SueloState() {}

SueloState *SueloState::getInstance() {
    if (instance == NULL) {
        instance = new SueloState();
    }
    return instance;
}

MarioState *SueloState::update(Mario *mario) {
    Ladder *ladder = stage->getLadder(mario->posX, mario->posY, mario->controls.up - mario->controls.down);
    if (ladder != NULL) {
        float distance = ladder->getX() - mario->posX;
        if (-4 <= distance && distance <= 4) {
            mario->posX = ladder->getX();
            TrepandoState *trepandoState = TrepandoState::getInstance();
            trepandoState->setLadder(ladder);
            return trepandoState;
        }
    }
    mario->velX = (mario->controls.right - mario->controls.left) * MARIO_VEL_X;
    mario->velY = GRAVEDAD;
    mario->posX += mario->velX * ((mario->posX < ANCHO_NIVEL - ANCHO_MARIO && 0 < mario->velX) || (0 < mario->posX && mario->velX < 0));
    mario->posY -= mario->velY;
    if (mario->controls.space || !stage->collide(&mario->posX, &mario->posY, &mario->velX, &mario->velY)) {
        mario->velX *= mario->controls.space;
        mario->velY = mario->controls.space * MARIO_VEL_SALTO;
        if(mario->velY > 0) {
            mario->audioObserver->update("salto");
        }
        return AireState::getInstance();
    }
    mario->estado = (mario->estado == DE_ESPALDAS) + (mario->velX != 0) * (CORRIENDO - (mario->estado == DE_ESPALDAS));
    return instance;
}