#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel1.h"
#include "Nivel1.h"

ComponenteVistaNivel1::ComponenteVistaNivel1(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void ComponenteVistaNivel1::mostrar(Nivel1* nivel1) {
    if(textura == NULL) {
        SDL_Surface* surface = IMG_Load(nivel1->rutaImagen.c_str());
        textura = SDL_CreateTextureFromSurface(renderer, surface);
    }

    SDL_RenderCopy(renderer, textura, NULL, NULL);
}