#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaMario.h"
#include "Entidad.h"
#include "Mario.hpp"
#include <string>
#include <iostream>

const std::string IMG_DEFAULT = "res/default.png";

const int TIEMPO_POR_FRAME = 10;
const int CANT_FRAMES = 4;

void ComponenteVistaMario::mostrar(Entidad* mario, std::string rutaImagen, SDL_Renderer* renderer) 
{ 
    if(textura == NULL) {
        SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
        if(surface == NULL) {
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }

        SDL_SetColorKey(surface, SDL_TRUE, *(Uint32*)(surface->pixels));

        textura = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    tiempo++;
    if(tiempo >= TIEMPO_POR_FRAME * CANT_FRAMES)
    {
        tiempo = 0;
    }

    int frameActual = tiempo / TIEMPO_POR_FRAME;
    
    if((frameTextura != frameActual) || frameActual == 0)
    {
        frameTextura = frameActual;
        rectSpritesheet.x = posXTextura[frameTextura];
        rectSpritesheet.y = posYTextura;
        rectSpritesheet.w = anchoTextura;
        rectSpritesheet.h = altoTextura;

        rectRender.x = mario->posX;
        rectRender.y = mario->posY;
        rectRender.w = mario->ancho;
        rectRender.h = mario->alto;    
    }
    
    // SDL_RenderCopy(renderer, textura, &rectSpritesheet, &rectRender);

    SDL_RendererFlip flip;

    switch (((Mario *) mario)->getEstado())
    {
        case REPOSO_DERECHA:
        case CORRIENDO_DERECHA:
            flip = SDL_FLIP_HORIZONTAL;
            break;

        default:
            flip = SDL_FLIP_NONE;
            break;
    }

    SDL_Rect rect = {mario->posX, mario->posY, mario->ancho, mario->alto};
    SDL_RenderCopyEx(renderer, textura, &rectSpritesheet, &rectRender, 0, NULL, flip);
}

void ComponenteVistaMario::inicializarTextura(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("res/Fuego.png");
    if(surface == NULL) {
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
    textura = SDL_CreateTextureFromSurface(renderer, surface);
}