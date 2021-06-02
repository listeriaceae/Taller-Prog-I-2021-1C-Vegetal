#pragma once
#include "../utils/punto.h"

class Plataforma {
    public:
        Plataforma(float x1, float y1, float x2, float y2);
        punto_t getPosicionAleatoria(int anchoEntidad);
        void getLimites(float *min, float *max);
        virtual ~Plataforma() = default;

    protected:
        punto_t extremo1;
        punto_t extremo2;
};