#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel.h"
#include "../logger.h"

ComponenteVistaNivel::ComponenteVistaNivel(SDL_Renderer* renderer, std::string rutaImagen) {
    this->renderer = renderer;
    setFondo(rutaImagen);
}

void ComponenteVistaNivel::setFondo(std::string rutaImagen) {
    SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
    if(surface == NULL) {
        logger::Logger::getInstance().logError("Image not found: " + rutaImagen);
        logger::Logger::getInstance().logDebug("Loading default image: " + IMG_DEFAULT);
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    textura = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void ComponenteVistaNivel::mostrar(std::list<Entidad*>* objetos, Uint32 frames) {
    SDL_RenderCopy(renderer, textura, NULL, NULL);
    
    std::list<Entidad*>::iterator it;
    for (it = objetos->begin(); it != objetos->end(); ++it) (*it)->mostrar(frames);
}