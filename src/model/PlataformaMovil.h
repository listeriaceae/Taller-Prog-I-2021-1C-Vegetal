#pragma once

#include "Entidad.h"

class PlataformaMovil : public Entidad {
    public:

        PlataformaMovil(int plataforma, int nivel);
        void mover();
        void mostrar();

    private:
        int direccion;
};