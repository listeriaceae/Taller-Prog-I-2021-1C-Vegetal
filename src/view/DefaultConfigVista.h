#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "../model/Entidad.h"

class DefaultConfigVista 
{
    public:
        void mostrar(Entidad* entidad, std::string rutaImagen, SDL_Renderer* renderer);
    
    private:
        SDL_Texture* textura = NULL;
};