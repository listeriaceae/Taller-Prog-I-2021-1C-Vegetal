#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

class Peach : public Entidad {
    public:

        Peach(SDL_Renderer *renderer);
        void mover();
        void mostrar(Uint32 frames);
        std::string getRutaImagen();

    private:
        ComponenteVistaEntidadEstatica* compVista;
        static std::string rutaImagen;
};