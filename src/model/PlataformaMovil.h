#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"


class PlataformaMovil : public Entidad {
    public:

    PlataformaMovil(int posX, int posY, int velX, int ancho, int alto);
    void mostrar(SDL_Renderer* renderer);
    void mover();
    std::string getRutaImagen();

    private:
    ComponenteVistaEntidadEstatica* compVista = new ComponenteVistaEntidadEstatica();
    int velX;
    std::string rutaImagen = "res/PlataformaMovil.png";
};