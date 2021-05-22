#pragma once
#include <string>
#include "../model/Entidad.h"
#include "../utils/window.hpp"

class ComponenteVistaEntidadEstatica {
    public:
    ComponenteVistaEntidadEstatica::ComponenteVistaEntidadEstatica(std::string rutaImagen, SDL_Rect rect, SDL_Renderer* renderer);
    void mostrar(Uint32 frames);
    
    private:
    static SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;

};