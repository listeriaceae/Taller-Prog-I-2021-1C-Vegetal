#pragma once

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "../view/ComponenteVistaNivel.h"
#include "Entidad.h"
#include "NivelBase.h"

class Nivel1 : public NivelBase
{
    public:
        Nivel1(SDL_Renderer* renderer, bool useDefaultConfig);
        void actualizarNivel();
        void actualizarVista(Uint32 frames);
        void agregarObjeto(Entidad* objeto);
        std::list<Entidad*>* getObjetos();
        void setFondo(std::string rutaImagen);
        void inicializarObjetos(SDL_Renderer* renderer);

    private:
        ComponenteVistaNivel* compVista;
        std::list<Entidad*> objetos;
        static std::string rutaImagen;
};