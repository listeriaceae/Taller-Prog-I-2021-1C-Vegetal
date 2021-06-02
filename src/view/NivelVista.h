#pragma once
#include <SDL2/SDL.h>
#include <list>
#include <vector>
#include <string>
#include "../model/Nivel.h"
#include "MarioVista.h"
#include "EntidadEstaticaVista.h"

class NivelVista {
    public:
        NivelVista(SDL_Renderer* renderer);
        void setBackground(std::string rutaImagen);
        void addPlayer(MarioVista *vista);
        virtual void update(estadoNivel_t *estadoNivel) = 0;
        virtual ~NivelVista();

    protected:
        static SDL_Renderer* renderer;
        SDL_Texture* texture;
        std::list<EntidadEstaticaVista*> entidadesVista;
        std::vector<MarioVista*> jugadoresVista;
};