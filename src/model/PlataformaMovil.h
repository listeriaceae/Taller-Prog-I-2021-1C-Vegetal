#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaPlataformaMovil.h"

class PlataformaMovil : public Entidad {
    public:

        PlataformaMovil(int plataforma, int nivel, SDL_Renderer *renderer);
        void mover();
        void mostrar();
        virtual ~PlataformaMovil() {
            delete compVista;
        };


    private:
        ComponenteVistaPlataformaMovil *compVista;
        int direccion;
        int limite;
};