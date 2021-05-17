#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaMario.h"
#include "Entidad.h"
#include <string>

const std::string IMG_DEFAULT = "res/default.png";

void ComponenteVistaMario::mostrar(Entidad* entidad, std::string rutaImagen, SDL_Renderer* renderer) {
    if(textura == NULL) {
        SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
        if(surface == NULL) {
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }

        Uint32 colorkey = SDL_MapRGB(surface->format, 255, 0, 0);
        SDL_SetColorKey(surface, SDL_TRUE, colorkey);


        // SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0)); //Hace que el fondo sea transparente
        textura = SDL_CreateTextureFromSurface(renderer, surface);
    }

    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

    SDL_Rect rect = {entidad->posX, entidad->posY, entidad->ancho, entidad->alto};
    // SDL_RenderCopy(renderer, textura, NULL, &rect);
    SDL_RenderCopyEx(renderer, textura, NULL, &rect, 0, NULL, flip);
}