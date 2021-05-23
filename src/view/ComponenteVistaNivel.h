#pragma once
#include <SDL2/SDL.h>
#include <list>
#include <string>
#include "../model/Entidad.h"

class ComponenteVistaNivel {
    public:
    
    ComponenteVistaNivel(SDL_Renderer* renderer, std::string rutaImagen);
    void setFondo(std::string rutaImagen);
    void mostrar(std::list<Entidad*>* objetos, Uint32 frames);
    
    private:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* textura = NULL;
};