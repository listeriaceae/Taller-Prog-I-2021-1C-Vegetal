#pragma once
#include <string>
#include <list>
#include <vector>
#include <SDL2/SDL.h>
#include "../utils/estadoJuego.h"
#include "MarioVista.h"
#include "EntidadEstaticaVista.h"

class NivelVista
{
public:
    NivelVista(SDL_Renderer *renderer);
    void setBackground(std::string rutaImagen);
    void addPlayers(unsigned int n);
    virtual void update(estadoJuego_t *estadoJuego) = 0;
    virtual ~NivelVista();

protected:
    static SDL_Renderer *renderer;
    SDL_Texture *texture;
    std::vector<MarioVista *> jugadoresVista;
    std::list<EntidadEstaticaVista *> entidadesVista;
};