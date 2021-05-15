#pragma once
#include "Entidad.h"
#include <SDL2/SDL.h>
#include <string>

class ComponenteVistaFuego {
    public:
    
    void mostrar(Entidad* entidad, SDL_Renderer* renderer);
    
    private:
    SDL_Texture* textura = NULL;
    SDL_Rect rectSpritesheet; //Rectangulo que determina que parte de la imagen cargar
    SDL_Rect rectRender; //Rectangulo que determina donde se va a renderear el objeto
    int frameTextura = 0;
    int tiempo = 0;
    int posXTextura[4] = {0, 24, 46, 70};
    int posYTextura = 0;
    int anchoTextura = 16;
    int altoTextura = 16;

    void inicializarTextura(SDL_Renderer* renderer);
};