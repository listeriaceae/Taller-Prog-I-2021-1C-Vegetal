#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.h"
#include "mario/MuriendoState.h"
#include "collider/Collider.h"
#include "collider/TestCollider.h"
#include "collider/NormalCollider.h"

Mario::Mario() : Entidad(0, 0, ANCHO_MARIO, ALTO_MARIO), state(SueloState::getInstance()) {}

void Mario::reset() {
    this->state = this->state->reset(*this);
}

void Mario::setStage(const Stage *stage) const {
    MarioState::setStage(stage);
}

void Mario::mover() {
    this->state = this->state->update(*this);
    if(this->controls.toggleTestMode == 1) {
        if(this->collider->getType() != TEST_MODE) {
            delete (this->collider);
            this->collider = new TestCollider();
            printf("Modo test: ON\n");
        } else {
            delete (this->collider);
            this->collider = new NormalCollider();
            printf("Modo test: OFF\n");
        }
    } 
        
    controls.space = 0;
}

void Mario::die() {
    if (contador != 0) return;
    ++contador;
    --lives;
    this->audioObserver.update(DEATH);
    this->state = MuriendoState::getInstance();
}

estadoMario_t Mario::getEstado() const {
    return {pos, estado, (collider->getType() == HAMMER), isEnabled, this->audioObserver.getState()};
}