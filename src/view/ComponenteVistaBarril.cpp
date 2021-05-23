#include <SDL2/SDL_image.h>
#include "ComponenteVistaBarril.h"
#include "../logger.h"
#include "../utils/window.hpp"

#define TIEMPO_POR_FRAME 3
#define CANT_FRAMES 4
#define SPRITE_INDEX_SIZE 24

const std::string IMG_BARRIL = "res/Barril.png";

SDL_Texture *ComponenteVistaBarril::texture = NULL;
SDL_Renderer *ComponenteVistaBarril::renderer = NULL;
int ComponenteVistaBarril::totalBarriles = 0;

ComponenteVistaBarril::ComponenteVistaBarril(SDL_Renderer *renderer) {
    if (this->texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load(IMG_BARRIL.c_str());
        if (surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: " + IMG_BARRIL);
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        } else SDL_SetColorKey(surface, SDL_TRUE, *(Uint32*)(surface->pixels));
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    rectSrc = {0, 0, ANCHO_BARRIL, ALTO_BARRIL};

    rectDst.w = round(ANCHO_BARRIL * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.h = round(ALTO_BARRIL * ALTO_PANTALLA / (float)ALTO_NIVEL);

    ++totalBarriles;
}

void ComponenteVistaBarril::mover(float x, float y) {
    rectDst.x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void ComponenteVistaBarril::mostrar(Uint32 frames) {
    tiempo = (tiempo + frames) % (TIEMPO_POR_FRAME * CANT_FRAMES);
    rectSrc.x = (tiempo / TIEMPO_POR_FRAME) * SPRITE_INDEX_SIZE;

    SDL_RenderCopy(renderer, texture, &rectSrc, &rectDst);
}

void ComponenteVistaBarril::free() {
    if (!(--totalBarriles)) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    delete this;
}