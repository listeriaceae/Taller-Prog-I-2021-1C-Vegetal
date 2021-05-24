#include <SDL2/SDL_image.h>
#include "ComponenteVistaEnemigoFuego.h"
#include "../logger.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define TIEMPO_POR_FRAME 4
#define CANT_FRAMES 2
#define SPRITE_INDEX_SIZE 24

const std::string IMG_ENEMIGO_FUEGO = "res/Enemy1.png";

SDL_Texture *ComponenteVistaEnemigoFuego::texture = NULL;
SDL_Renderer *ComponenteVistaEnemigoFuego::renderer = NULL;

ComponenteVistaEnemigoFuego::ComponenteVistaEnemigoFuego(SDL_Renderer *renderer) {
    if (this->texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load(IMG_ENEMIGO_FUEGO.c_str());
        if (surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: " + IMG_ENEMIGO_FUEGO);
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    rectSrc = {0, 0, ANCHO_ENEMIGO_FUEGO, ALTO_ENEMIGO_FUEGO};

    rectDst.w = round(ANCHO_ENEMIGO_FUEGO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.h = round(ALTO_ENEMIGO_FUEGO * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void ComponenteVistaEnemigoFuego::mover(float x, float y) {
    rectDst.x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void ComponenteVistaEnemigoFuego::mostrar() {
    tiempo = (tiempo + 1) % (TIEMPO_POR_FRAME * CANT_FRAMES);
    rectSrc.x = (tiempo / TIEMPO_POR_FRAME) * SPRITE_INDEX_SIZE;

    SDL_RenderCopy(renderer, texture, &rectSrc, &rectDst);
}