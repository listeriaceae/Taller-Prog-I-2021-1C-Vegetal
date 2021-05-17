#pragma once
#include <string>
#include "Entidad.h"
#include "Rendereable.h"
#include "ComponenteVistaMario.h"

class Mario : public Entidad, public Rendereable {
    public: 
        Mario(int posX, int posY, int velX, int ancho, int alto);
        void mostrar(SDL_Renderer* renderer);
        void mover();
        std::string getRutaImagen();
         //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

    private: 
        ComponenteVistaMario* compVista = new ComponenteVistaMario();
        int velX;
        int posXInicial;
        int posYInicial;
        std::string rutaImagen = "res/Mario-3.png";
};