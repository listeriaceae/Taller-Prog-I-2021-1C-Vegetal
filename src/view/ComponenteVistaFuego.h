#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../model/Entidad.h"

#define ANCHO_FUEGO 16
#define ALTO_FUEGO 16
#define SPRITE_INDEX 24

class ComponenteVistaFuego {
    public:
        void mostrar(SDL_Renderer* renderer);
        ComponenteVistaFuego(int x, int y, SDL_Renderer* renderer);
    
    private:
        static SDL_Texture* texture;
        static SDL_Rect rectSpritesheet; //Rectangulo que determina que parte de la imagen cargar
        static int tiempo;
        static int total_fuegos;
        static int fue_actualizado;
        SDL_Rect rectRender; //Rectangulo que determina donde se va a renderear el objeto
};