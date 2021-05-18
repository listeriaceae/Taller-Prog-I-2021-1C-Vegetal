#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaMario.h"
#include "Entidad.h"
#include "Mario.hpp"
#include <string>
#include <iostream>

const std::string IMG_DEFAULT = "res/default.png";

void ComponenteVistaMario::mostrar(Entidad* mario, std::string rutaImagen, SDL_Renderer* renderer) { 
    if(textura == NULL) {
        SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
        if(surface == NULL) {
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        // std::cout << "surface->format=" << surface->format << std::endl;

        SDL_SetColorKey(surface, SDL_TRUE, *(Uint32*)(surface->pixels));

        textura = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    SDL_RendererFlip flip;

    switch (((Mario *) mario)->getEstado())
    {
        case REPOSO_DERECHA:
        case CORRIENDO_DERECHA:
            flip = SDL_FLIP_HORIZONTAL;
            break;

        default:
            flip = SDL_FLIP_NONE;
            break;
    }

    SDL_Rect rect = {mario->posX, mario->posY, mario->ancho, mario->alto};
    SDL_RenderCopyEx(renderer, textura, NULL, &rect, 0, NULL, flip);
}