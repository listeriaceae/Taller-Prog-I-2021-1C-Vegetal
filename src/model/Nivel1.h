#pragma once

#include <list>
#include "stage/MovingPlatform.h"
#include "stage/Ladder.h"
#include "Nivel.h"

class Nivel1 : public Nivel
{
    public:
        Nivel1();
        void addEnemies(unsigned int amount);
        void update();
        estadoNivel_t *getEstado();
        ~Nivel1();

    private:
        MovingPlatform * movingPlatforms[12];

        void initPlatforms();
        void updatePlatforms();
        void initLadders();
};