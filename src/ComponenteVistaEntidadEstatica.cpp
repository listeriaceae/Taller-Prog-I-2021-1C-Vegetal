#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaEntidadEstatica.h"
#include "Entidad.h"

void ComponenteVistaEntidadEstatica::mostrar(Entidad* entidad, std::string rutaImagen, SDL_Renderer* renderer) {
    if(textura == NULL) {
        SDL_Surface* surface = IMG_Load(rutaImagen.c_str());
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0)); //Hace que el fondo sea transparente
        textura = SDL_CreateTextureFromSurface(renderer, surface);
    }

    SDL_Rect rect = {entidad->posX, entidad->posY, entidad->ancho, entidad->alto};
    SDL_RenderCopy(renderer, textura, NULL, &rect);
}