#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Entidad.h"
#include "../view/ComponenteVistaBarril.h"

class Barril : public Entidad {
    public:
        Barril(float x, float y, SDL_Renderer *renderer);
        void mover();
        void mostrar();
        bool estaEnNivel();
        virtual ~Barril() {
            delete compVista;
        };

    private:
        ComponenteVistaBarril* compVista;
        float velX;
        float velY;
};