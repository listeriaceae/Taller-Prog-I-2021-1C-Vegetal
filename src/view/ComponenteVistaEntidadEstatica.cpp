#include <SDL2/SDL_image.h>
#include "ComponenteVistaEntidadEstatica.h"
#include "../logger.h"
#include "../utils/window.hpp"

SDL_Renderer *ComponenteVistaEntidadEstatica::renderer = NULL;

ComponenteVistaEntidadEstatica::ComponenteVistaEntidadEstatica(std::string rutaImagen, SDL_Rect *rect, SDL_Renderer* renderer) {
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
    if (surface == NULL) {
        logger::Logger::getInstance().logError("Image not found: " + rutaImagen);
        logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_free(surface);
    
    this->rect.x = round(rect->x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    this->rect.y = round(rect->y * ALTO_PANTALLA / (float)ALTO_NIVEL);
    this->rect.w = round(rect->w * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    this->rect.h = round(rect->h * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void ComponenteVistaEntidadEstatica::mostrar(Uint32 frames) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}