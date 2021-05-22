#pragma once

#include <string>
#include "Entidad.h"
#include "../view/DefaultConfigVista.h"

class DefaultConfig : public Entidad {
    public:
        DefaultConfig(int posX, int posY, int ancho, int alto);
        void mostrar(SDL_Renderer* renderer);
        void mover();
        std::string getRutaImagen();

    private:
        DefaultConfigVista * compVista = new DefaultConfigVista();
        std::string rutaImagen = "res/default-config.png";
};