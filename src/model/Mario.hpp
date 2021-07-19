#pragma once
#include "Entidad.h"
#include "mario/MarioState.h"
#include "../controller/AudioObserver.h"
#include "../utils/marioStructs.h"
#include "collider/TestCollider.h"
#include "collider/NormalCollider.h"
#include "collider/HammerCollider.h"
#include "../utils/Constants.hpp"
#include "Hammer.h"

class MarioState;
class Collider;

class Mario : public Entidad
{
public:
    Mario();
    void reset();
    void setStageAndReset(Stage *stage);
    void mover();
    void disable() { isEnabled = false; controls = {0, 0, 0, 0, 0, 0}; }
    void enable() { isEnabled = true; }
    estadoMario_t getEstado() const;
    void die();
    dimensiones_t dimensions() const;
    unsigned char getScore();
    void addPoints(unsigned char points);
    bool getIsLevelCompleted();
    void collide(EnemigoFuego* fuego);
    void collide(Barril* barril);
    void collide(Hammer* barril);
    void toggleTestMode();
    AudioObserver audioObserver{};
    char lives{MARIO_LIVES};
    controls_t controls{0, 0, 0, 0, 0, 0};
    unsigned char contador{0};
    char estado{REPOSO};
    float velX{0.f};
    float velY{0.f};
    float climbMin{256};
    float climbMax{0};
    Collider* collider = new NormalCollider();
    Direccion direccion = DERECHA;
private:
    const MarioState *state;
    bool isEnabled{true};
    unsigned char score{0};
    void setCollider(ColliderType colliderType);
    
};