#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaPolea.h"
#include "../model/Entidad.h"
#include <iostream>
#include "../logger.h"

const std::string IMG_DEFAULT = "res/default.png";
const std::string IMG_POLEAS = "res/Polea.png";
const int TIEMPO_POR_FRAME = 7;
const int CANT_FRAMES = 3;

ComponenteVistaPolea::ComponenteVistaPolea(std::string direccion) {
    this->direccion = direccion;
}
void ComponenteVistaPolea::mostrar(Entidad* entidad, SDL_Renderer* renderer) {
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

    SDL_RenderCopyEx(renderer, textura, &rectSpritesheet, &rectRender, 0, NULL, flip);
}
void ComponenteVistaPolea::inicializarTextura(SDL_Renderer* renderer) {

    SDL_Surface* surface = IMG_Load(IMG_POLEAS.c_str());
    if(surface == NULL) {
        logger::Logger::getInstance().logError("Image not found: " + IMG_POLEAS);
        logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
    textura = SDL_CreateTextureFromSurface(renderer, surface);
    if(direccion.compare("izquierda") == 0) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if(direccion.compare("derecha") == 0) {
        flip = SDL_FLIP_VERTICAL; //Para que giren todas las poleas en el mismo sentido
    }
}