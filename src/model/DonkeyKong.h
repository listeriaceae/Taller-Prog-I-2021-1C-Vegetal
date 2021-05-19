#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

class DonkeyKong : public Entidad {
    public:

    DonkeyKong(int posX, int posY, int ancho, int alto);
    void mostrar(SDL_Renderer* renderer);
    void mover();
    std::string getRutaImagen();

    private:
    ComponenteVistaEntidadEstatica* compVista = new ComponenteVistaEntidadEstatica();
    std::string rutaImagen = "res/DonkeyKong.png";
};