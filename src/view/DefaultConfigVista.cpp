#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "DefaultConfigVista.h"
#include "../logger.h"
#include "../model/Entidad.h"

const std::string IMG_DEFAULT = "res/default.png";

void DefaultConfigVista::mostrar(Entidad* entidad, std::string rutaImagen, SDL_Renderer* renderer) {
    if(textura == NULL) {
        SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
        if(surface == NULL) {
            logger::Logger::getInstance().logError("Image not found: res/default-config.png");
            logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
        textura = SDL_CreateTextureFromSurface(renderer, surface);
    }

    SDL_Rect rect = {entidad->posX, entidad->posY, entidad->ancho, entidad->alto};
    SDL_RenderCopy(renderer, textura, NULL, &rect);
}