#include <string>
#include <SDL2/SDL_image.h>
#include "FireBarrelVista.h"
#include "../logger.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

const std::string IMG_FIRE_BARREL = "res/FireBarrel.png";

SDL_Texture *FireBarrelVista::texture = NULL;

FireBarrelVista::FireBarrelVista(SDL_Renderer* renderer)
: EntidadEstaticaVista() {
    if (texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load(IMG_FIRE_BARREL.c_str());
        if (surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: " + IMG_FIRE_BARREL);
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    this->rect.x = round(POSX_BARRIL * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    this->rect.y = round(POSY_BARRIL * ALTO_PANTALLA / (float)ALTO_NIVEL);
    this->rect.w = round(ANCHO_FIRE_BARREL * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    this->rect.h = round(ALTO_FIRE_BARREL * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void FireBarrelVista::mostrar() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
