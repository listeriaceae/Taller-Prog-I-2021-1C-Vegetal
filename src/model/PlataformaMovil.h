#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaPlataformaMovil.h"

class PlataformaMovil : public Entidad {
    public:

    PlataformaMovil(int plataforma, int nivel, SDL_Renderer *renderer);
    void mover();
    void mostrar(Uint32 frames);
    std::string getRutaImagen();

    private:
    ComponenteVistaPlataformaMovil *compVista;
    int direccion;
    int limite;
    static std::string rutaImagen;
};