#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel1.h"
#include "Nivel1.h"

const std::string IMG_DEFAULT = "res/default.png";

ComponenteVistaNivel1::ComponenteVistaNivel1(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void ComponenteVistaNivel1::mostrar(Nivel1* nivel1) {
    mostrarFondo(nivel1);
    mostrarObjetos(nivel1);
}

void ComponenteVistaNivel1::mostrarFondo(Nivel1* nivel1) {
    if(textura == NULL) {
        SDL_Surface* surface = IMG_Load(nivel1->rutaImagen.c_str());
        if(surface == NULL) {
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        textura = SDL_CreateTextureFromSurface(renderer, surface);
    }

    SDL_RenderCopy(renderer, textura, NULL, NULL);
}
void ComponenteVistaNivel1::mostrarObjetos(Nivel1* nivel1) {
    std::list<Entidad*>::iterator it;
    std::list<Entidad*>* objetos = nivel1->getObjetos();
    
    for (it = objetos->begin(); it != objetos->end(); ++it){
        (*it)->mostrar(renderer);
    }
}