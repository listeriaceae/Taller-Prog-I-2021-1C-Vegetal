#include <SDL2/SDL_image.h>
#include "ComponenteVistaPlataformaMovil.h"
#include "../logger.h"
#include "../utils/window.hpp"

const std::string IMG_PLATAFORMA_MOVIL = "res/PlataformaMovil.png";

SDL_Texture *ComponenteVistaPlataformaMovil::texture = NULL;
SDL_Renderer *ComponenteVistaPlataformaMovil::renderer = NULL;

ComponenteVistaPlataformaMovil::ComponenteVistaPlataformaMovil(float y, SDL_Renderer *renderer) {
    if (this->texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load(IMG_PLATAFORMA_MOVIL.c_str());
        if (surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: " + IMG_PLATAFORMA_MOVIL);
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    rectDst.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
    rectDst.w = round(ANCHO_PLATAFORMA * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.h = round(ALTO_PLATAFORMA * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void ComponenteVistaPlataformaMovil::mover(float x) {
    rectDst.x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
}

void ComponenteVistaPlataformaMovil::mostrar(Uint32 frames) {
    SDL_RenderCopy(renderer, texture, NULL, &rectDst);
}