#include "ComponenteVistaEnemigoFuego.h"
#include "../logger.h"
#include "../utils/window.hpp"

const std::string IMG_ENEMIGO_FUEGO = "res/enemy1.png";

SDL_Texture *ComponenteVistaEnemigoFuego::texture = NULL;
std::string ComponenteVistaEnemigoFuego::rutaImagen = IMG_ENEMIGO_FUEGO;

ComponenteVistaEnemigoFuego::ComponenteVistaEnemigoFuego(SDL_Renderer *renderer) {
    if (this->texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load(IMG_ENEMIGO_FUEGO.c_str());
        if (surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: " + IMG_ENEMIGO_FUEGO);
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
            this->rutaImagen = IMG_DEFAULT;
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    rectSrc.w = {0, 0, ANCHO_ENEMIGO_FUEGO, ALTO_ENEMIGO_FUEGO};

    rectDst.w = round(ANCHO_ENEMIGO_FUEGO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.h = round(ALTO_ENEMIGO_FUEGO * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void ComponenteVistaEnemigoFuego::mover(float x, float y) {
    rectDst.x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void ComponenteVistaEnemigoFuego::mostrar(Uint32 frames) {
    SDL_RenderCopy(renderer, texture, &rectSrc, &rectDst);
}

std::string ComponenteVistaEnemigoFuego::getRutaImagen() {
    return rutaImagen;
}