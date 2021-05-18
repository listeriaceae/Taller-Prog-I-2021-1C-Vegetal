#pragma once

#include <string>
#include "Entidad.h"
#include "ComponenteVistaEntidadEstatica.h"

class Peach : public Entidad {
    public:

    Peach(int posX, int posY, int ancho, int alto);
    void mostrar(SDL_Renderer* renderer);
    void mover();
    std::string getRutaImagen();

    private:
    ComponenteVistaEntidadEstatica* compVista = new ComponenteVistaEntidadEstatica();
    std::string rutaImagen = "res/Peach.png";
};