#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel1.h"
#include "../model/Nivel1.h"

const std::string IMG_DEFAULT = "res/default.png";

ComponenteVistaNivel1::ComponenteVistaNivel1(SDL_Renderer* renderer, std::string rutaImagen) {
    this->renderer = renderer;
    setFondo(rutaImagen);
}

void ComponenteVistaNivel1::setFondo(std::string rutaImagen) {
    SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
    if(surface == NULL) {
        surface = IMG_Load(IMG_DEFAULT.c_str());
    }
    textura = SDL_CreateTextureFromSurface(renderer, surface);
}

void ComponenteVistaNivel1::mostrar(std::list<Entidad*>* objetos) {
    mostrarFondo();
    mostrarObjetos(objetos);
}

void ComponenteVistaNivel1::mostrarFondo() {
    SDL_RenderCopy(renderer, textura, NULL, NULL);
}

void ComponenteVistaNivel1::mostrarObjetos(std::list<Entidad*>* objetos) {
    std::list<Entidad*>::iterator it;
    
    for (it = objetos->begin(); it != objetos->end(); ++it){
        (*it)->mostrar(renderer);
    }
}