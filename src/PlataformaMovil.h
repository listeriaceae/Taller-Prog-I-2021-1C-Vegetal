#pragma once

#include <string>
#include "Entidad.h"
#include "Rendereable.h"
#include "ComponenteVistaEntidadEstatica.h"


class PlataformaMovil : public Entidad, public Rendereable {
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