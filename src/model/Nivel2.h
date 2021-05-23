#pragma once

#include <string>
#include <list>
#include <SDL2/SDL.h>
#include <vector>
#include "Barril.h"
#include "../view/ComponenteVistaNivel.h"
#include "NivelBase.h"

class Nivel2: public NivelBase {
    public:
        Nivel2(SDL_Renderer *renderer, bool useDefaultConfig);
        void actualizarNivel();
        void actualizarVista(Uint32 frames);
        void agregarObjeto(Entidad *objeto);
        std::list<Entidad*>* getObjetos();
        void setFondo(std::string rutaImagen);
        void inicializarObjetos(SDL_Renderer *renderer);

    private:
        SDL_Renderer *renderer;
        static std::string rutaImagen;
        ComponenteVistaNivel* compVista;
        std::vector<Barril*> barriles;
        std::list<Entidad*> objetos;
        Uint32 tick;

        void agregarBarril();
        void updateBarriles();
        void mostrarBarriles(Uint32 frames);
};