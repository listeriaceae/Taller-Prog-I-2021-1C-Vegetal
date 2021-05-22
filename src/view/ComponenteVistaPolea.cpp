#include <string>
#include "ComponenteVistaPolea.h"
#include "../logger.h"
#include "../utils/window.hpp"

#define TIEMPO_POR_FRAME 7
#define CANT_FRAMES 3

const std::string IMG_DEFAULT = "res/default.png";
const std::string IMG_POLEAS = "res/Polea.png";

SDL_Texture* ComponenteVistaPolea::texture = NULL;
int ComponenteVistaPolea::fueActualizado, ComponenteVistaPolea::tiempo, ComponenteVistaPolea::totalPoleas = 0;

ComponenteVistaPolea::ComponenteVistaPolea(int x, int y, int direccion, SDL_Renderer *renderer) {
    if (texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load(IMG_POLEAS.c_str());
        if (surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: " + IMG_POLEAS);
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        rectSrc.y = 0;
        rectSrc.w = ANCHO_POLEA;
        rectSrc.h = ALTO_POLEA;
    }

    rectDst.x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
    rectDst.w = round(ANCHO_POLEA * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.h = round(ALTO_POLEA * ALTO_PANTALLA / (float)ALTO_NIVEL);
    
    flip = (SDL_RendererFlip)((direccion << 1) | direccion);

    totalPoleas++;
}

void ComponenteVistaPolea::mostrar(Uint32 frames) {
    tiempo = (tiempo + (!fueActualizado) * frames) % (TIEMPO_POR_FRAME * CANT_FRAMES);
    rectSrc.x = (tiempo / TIEMPO_POR_FRAME) * SPRITE_INDEX;
    fueActualizado = (fueActualizado + 1) % totalPoleas;

    SDL_RenderCopyEx(renderer, texture, &rectSrc, &rectDst, 0, NULL, flip);
}