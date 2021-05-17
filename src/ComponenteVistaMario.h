#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "Entidad.h"


class ComponenteVistaMario 
{
    public:
        void mostrar(Entidad* entidad, std::string rutaImagen, SDL_Renderer* renderer);

    private:
        SDL_Texture* textura = NULL;
};