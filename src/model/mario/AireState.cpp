#include "AireState.h"
#include "SueloState.h"
#include "../../utils/Constants.hpp"

AireState *AireState::instance = NULL;

AireState::AireState() {}

AireState *AireState::getInstance() {
    if (instance == NULL) {
        instance = new AireState();
    }
    return instance;
}

MarioState *AireState::update(Mario *mario) {
    mario->estado += (SALTANDO - mario->estado) * (mario->velY > 0);
    mario->velX -= mario->velX * 2 * !((mario->posX < ANCHO_NIVEL - ANCHO_MARIO && 0 < mario->velX) || (0 < mario->posX && mario->velX < 0));
    mario->velY += GRAVEDAD;
    mario->posX += mario->velX;
    mario->posY -= mario->velY;
    if (stage->collide(&mario->posX, &mario->posY, &mario->velX, &mario->velY)) return SueloState::getInstance();

    if (mario->posY > ALTO_NIVEL - ALTO_MARIO) {             // Aca moriria mario
        mario->die();
        mario->reset();
    }
    return instance;
}