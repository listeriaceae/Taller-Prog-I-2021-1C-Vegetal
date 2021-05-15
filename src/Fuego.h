#pragma once
#include <SDL2/SDL.h>

class Fuego {
    public:
    
    Fuego(int posX, int posY, int ancho, int alto);

    void mostrar(SDL_Renderer* renderer);

    private:
    SDL_Texture* textura = NULL;
    SDL_Rect rectSpritesheet; //Rectangulo que determina que parte de la imagen cargar
    SDL_Rect rectRender; //Rectangulo que determina donde se va a renderear el objeto
    int frame = 0;
    int frameActual = 0;
    int posX = 172;
    int posY = 544;
    int posXTextura[4] = {0, 24, 46, 70};
    int anchoTextura = 16;
    int altoTextura = 16;
    int ancho = 56;
    int alto = 56;

    void inicializarTextura(SDL_Renderer* renderer);
};