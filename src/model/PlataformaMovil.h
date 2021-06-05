#pragma once

#include "Plataforma.h"

class PlataformaMovil : public Plataforma {
    public:
        PlataformaMovil(int plataforma, int nivel);
        void mover();
        punto_t getPos();

    private:
        int direccion;
};