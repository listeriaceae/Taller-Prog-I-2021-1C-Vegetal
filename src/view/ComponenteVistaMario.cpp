#include <string>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaMario.h"
#include "../model/Mario.hpp"
#include "../logger.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define MARIO_SPRITE_INDEX_SIZE 24
#define MARIO_SALTO_INDEX 14
#define TIEMPO_POR_FRAME 4
#define CANT_FRAMES 4

const std::string IMG_MARIO = "res/Mario.png";

SDL_Renderer *ComponenteVistaMario::renderer = NULL;

ComponenteVistaMario::ComponenteVistaMario(SDL_Renderer *renderer) {
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load(IMG_MARIO.c_str());

    if(surface == NULL) {
        logger::Logger::getInstance().logError("Mario image not found: " + IMG_MARIO);
        logger::Logger::getInstance().logDebug("Loading Mario default image: " + IMG_DEFAULT);
        surface = IMG_Load(IMG_DEFAULT.c_str());
    } else { 
        SDL_SetColorKey(surface, SDL_TRUE, *(Uint32*)(surface->pixels));
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rectSrc.y = 0;
    rectSrc.w = ANCHO_MARIO;
    rectSrc.h = ALTO_MARIO;

    rectDst.w = round(ANCHO_MARIO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    rectDst.h = round(ALTO_MARIO * ALTO_PANTALLA / (float)ALTO_NIVEL);

    tiempo = 0;
    flip = SDL_FLIP_HORIZONTAL;
}

void ComponenteVistaMario::mostrar(float x, float y, char estado) {

    tiempo = (tiempo + 1) % (TIEMPO_POR_FRAME * CANT_FRAMES);
    int next_x = round(x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    switch(estado) {
        case REPOSO:
            updateReposo();
            break;
        case CORRIENDO:
            updateCorriendo(next_x);
            break;
        case SALTANDO:
            updateSaltando();
            break;
        case TREPANDO:
            updateTrepando();
            break;
        default:
            break;
    }
    rectDst.x = next_x;
    rectDst.y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);

    SDL_RenderCopyEx(renderer, texture, &rectSrc, &rectDst, 0., NULL, flip);
}

void ComponenteVistaMario::updateReposo() {
    rectSrc.x = 0;
}

void ComponenteVistaMario::updateCorriendo(int next_x) {
    flip = (SDL_RendererFlip)(rectDst.x < next_x);
    int frameActual = (tiempo / TIEMPO_POR_FRAME);
    rectSrc.x = ((frameActual & 1) << ((frameActual & 2) >> 1)) * MARIO_SPRITE_INDEX_SIZE;  // 0, 1, 0, 2...
}

void ComponenteVistaMario::updateSaltando() {
    rectSrc.x = MARIO_SALTO_INDEX * MARIO_SPRITE_INDEX_SIZE;
}

void ComponenteVistaMario::updateTrepando() {
    // TREPANDO
    int frameActual = (tiempo / TIEMPO_POR_FRAME);
    rectSrc.x = 142;
    // La imagen de Mario de espaldas es mas ancha que la de perfil
    rectSrc.w = 20;
}

void ComponenteVistaMario::free() {
    SDL_DestroyTexture(texture);
}