#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaFuego.h"
#include "../model/Entidad.h"
#include <iostream>

const std::string IMG_DEFAULT = "res/default.png";
const int TIEMPO_POR_FRAME = 3;
const int CANT_FRAMES = 4;

void ComponenteVistaFuego::mostrar(Entidad* entidad, SDL_Renderer* renderer) {
    if(textura == NULL)
        inicializarTextura(renderer);

    tiempo++;
    if(tiempo >= TIEMPO_POR_FRAME * CANT_FRAMES)
        tiempo = 0;

    int frameActual = tiempo / TIEMPO_POR_FRAME;
    if((frameTextura != frameActual) || frameActual == 0) {
        frameTextura = frameActual;
        rectSpritesheet.x = posXTextura[frameTextura];
        rectSpritesheet.y = posYTextura;
        rectSpritesheet.w = anchoTextura;
        rectSpritesheet.h = altoTextura;

        rectRender.x = entidad->posX;
        rectRender.y = entidad->posY;
        rectRender.w = entidad->ancho;
        rectRender.h = entidad->alto;    
    }
    SDL_RenderCopy(renderer, textura, &rectSpritesheet, &rectRender);
}

void ComponenteVistaFuego::inicializarTextura(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("res/Fuego.png");
    if(surface == NULL) {
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
    textura = SDL_CreateTextureFromSurface(renderer, surface);
}