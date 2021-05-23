#pragma once

#include <string>
#include <SDL2/SDL.h>

class ComponenteVistaEntidadEstatica {
    public:
        ComponenteVistaEntidadEstatica(std::string rutaImagen, SDL_Rect *rect, SDL_Renderer* renderer);
        void mostrar(Uint32 frames);
    
    private:
        static SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect rect;
        static Uint32 frames;

};