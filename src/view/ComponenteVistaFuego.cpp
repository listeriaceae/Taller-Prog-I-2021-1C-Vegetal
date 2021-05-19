#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaFuego.h"
#include "../model/Entidad.h"
#include <iostream>
#include "../window.hpp"

const std::string IMG_DEFAULT = "res/default.png";
const int TIEMPO_POR_FRAME = 10;
const int CANT_FRAMES = 4;

SDL_Texture* ComponenteVistaFuego::texture = NULL;
SDL_Rect ComponenteVistaFuego::rectSpritesheet;
int ComponenteVistaFuego::tiempo, ComponenteVistaFuego::total_fuegos, ComponenteVistaFuego::fue_actualizado = 0;

ComponenteVistaFuego::ComponenteVistaFuego(int x, int y, SDL_Renderer* renderer) {
    if (texture == NULL) {
        SDL_Surface* surface = IMG_Load("res/Fuego.png");
        if(surface == NULL) {
            surface = IMG_Load(IMG_DEFAULT.c_str());
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        rectSpritesheet.y = 0;
        rectSpritesheet.w = ANCHO_FUEGO;
        rectSpritesheet.h = ALTO_FUEGO;
    }

    rectRender.x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectRender.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
    rectRender.w = round(ANCHO_FUEGO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectRender.h = round(ALTO_FUEGO * ALTO_PANTALLA / (float)ALTO_NIVEL);

    fue_actualizado = 0;
    total_fuegos++;
}

void ComponenteVistaFuego::mostrar(SDL_Renderer* renderer) {
    if (!fue_actualizado) {
        rectSpritesheet.x = (tiempo / TIEMPO_POR_FRAME) * SPRITE_INDEX;
        tiempo = (tiempo + 1) % (TIEMPO_POR_FRAME * CANT_FRAMES);
    }
    fue_actualizado = (fue_actualizado + 1) % total_fuegos;

    SDL_RenderCopy(renderer, texture, &rectSpritesheet, &rectRender);
}