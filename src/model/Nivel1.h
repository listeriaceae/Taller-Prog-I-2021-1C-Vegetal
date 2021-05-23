#pragma once

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "../view/ComponenteVistaNivel.h"
#include "Entidad.h"

class Nivel1 {
    public:

        Nivel1(SDL_Renderer* renderer);
        void actualizarNivel();
        void actualizarVista(Uint32 frames);
        void agregarObjeto(Entidad* objeto);
        std::list<Entidad*>* getObjetos();
        void setFondo(std::string rutaImagen);
        void inicializarObjetos(SDL_Renderer* renderer);

    private:
        static std::string rutaImagen;
        ComponenteVistaNivel* compVista;
        std::list<Entidad*> objetos;
};