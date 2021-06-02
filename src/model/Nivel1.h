#pragma once

#include <list>
#include "PlataformaMovil.h"
#include "Nivel.h"

class Nivel1 : public Nivel
{
    public:
        Nivel1();
        void addEnemies(unsigned int amount);
        void update();
        estadoNivel_t* getEstado();
        ~Nivel1();

    private:
        std::list<PlataformaMovil*> plataformasMoviles;

        void updatePlatforms();
        void updateEnemies();
};