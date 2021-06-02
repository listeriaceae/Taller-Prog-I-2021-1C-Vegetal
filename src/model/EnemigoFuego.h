#pragma once

#include "Entidad.h"

class EnemigoFuego : public Entidad {
    public:
        EnemigoFuego(float x, float y, int velX);
        void mover();

    private: 
        int velX;
        float posXInicial;
};