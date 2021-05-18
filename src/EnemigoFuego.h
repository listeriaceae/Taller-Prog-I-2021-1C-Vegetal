#pragma once
#include <string>
#include "Entidad.h"
#include "ComponenteVistaEntidadEstatica.h"

class EnemigoFuego : public Entidad{
    public: 
    EnemigoFuego(int posX, int posY, int velX, int ancho, int alto);
    void mostrar(SDL_Renderer* renderer);
    void mover();
    std::string getRutaImagen();

    private: 
    ComponenteVistaEntidadEstatica* compVista = new ComponenteVistaEntidadEstatica();
    int velX;
    int posXInicial;
    int posYInicial;
    std::string rutaImagen = "res/EnemigoFuego.png";
};