#include "Fuego.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int TIEMPO_POR_FRAME = 20;
const int CANT_FRAMES = 4;
Fuego::Fuego(int posX, int posY, int ancho, int alto) {
    this->posX = posX;
    this->posY = posY;
    this->ancho = ancho;
    this->alto = alto;
}

void Fuego::mostrar(SDL_Renderer* renderer) {
    if(textura == NULL)
        inicializarTextura(renderer);

    frame++;
    if(frame > TIEMPO_POR_FRAME * CANT_FRAMES)
        frame = 0;

    if(frame != frameActual) {
        frameActual = frame / TIEMPO_POR_FRAME;
        rectSpritesheet.x = posXTextura[frameActual];
        rectSpritesheet.y = 0;
        rectSpritesheet.w = anchoTextura;
        rectSpritesheet.h = altoTextura;

        rectRender.x = posX;
        rectRender.y = posY;
        rectRender.w = ancho;
        rectRender.h = alto;

        SDL_RenderCopy(renderer, textura, &rectSpritesheet, &rectRender);
    }
}

void Fuego::inicializarTextura(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("res/Fuego.png");
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
    textura = SDL_CreateTextureFromSurface(renderer, surface);
}