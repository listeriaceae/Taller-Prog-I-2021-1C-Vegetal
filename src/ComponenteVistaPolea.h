#pragma once
#include "Entidad.h"
#include <SDL2/SDL.h>
#include <string>

class ComponenteVistaPolea {
    public:
    
    ComponenteVistaPolea(std::string direccion);
    void mostrar(Entidad* entidad, SDL_Renderer* renderer);
    
    private:
    std::string direccion = "izquierda";
    SDL_Texture* textura = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect rectSpritesheet; //Rectangulo que determina que parte de la imagen cargar
    SDL_Rect rectRender; //Rectangulo que determina donde se va a renderear el objeto
    int frameTextura = 0;
    int tiempo = 0;
    int posXTextura[3] = {0, 24, 48};
    int posYTextura = 0;
    int anchoTextura = 11;
    int altoTextura = 10;

    void inicializarTextura(SDL_Renderer* renderer);
};