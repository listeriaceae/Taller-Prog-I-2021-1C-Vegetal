#include <SDL2/SDL_image.h>
#include "NivelVista.h"
#include "../logger.h"
#include "../utils/Constants.hpp"

SDL_Renderer* NivelVista::renderer = NULL;

NivelVista::NivelVista(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

void NivelVista::addPlayer(MarioVista *vista) {
    jugadoresVista.push_back(vista);
}

void NivelVista::setBackground(std::string rutaImagen) {
    SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
    if(surface == NULL) {
        logger::Logger::getInstance().logError("Image not found: " + rutaImagen);
        logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

NivelVista::~NivelVista() {
    SDL_DestroyTexture(texture);

    for (MarioVista *vista : jugadoresVista) delete vista;
    jugadoresVista.clear();

    for (EntidadEstaticaVista *vista : entidadesVista) delete vista;
    entidadesVista.clear();
}