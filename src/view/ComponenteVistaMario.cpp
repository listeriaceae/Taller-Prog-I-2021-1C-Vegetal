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
    int next_y = round(y * ALTO_PANTALLA / (float)ALTO_NIVEL);
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
        case TREPANDO_REPOSO:
            updateTrepando(y);
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

void ComponenteVistaMario::updateTrepando(int y) {
    // TREPANDO
    // La imagen de Mario de espaldas es mas ancha que la de perfil
    rectSrc.w = 20;
    rectSrc.x = 70;

    bool flag = true;
    if (y >= 232){
        rectSrc.x = 142;
    }
    else if (y >= 229) // 1 escalon
        flag = true;
    else if (y >= 225) // 2 escalon
        flag = false;
    else if (y >= 221) // 3
        flag = true;
    else if (y >= 217) // 4
        flag = false;
    else if (y >= 213)
        flag = true;
    else if (y >= 209)
        flag = false;
    else if (y >= 205)
        flag = true;
    else if (y >= 201) {
        flag = false;
    } else if (y >= 197) {
        flag = true;
    } else if (y >= 193) {
        rectSrc.x = 95;
    } else if (y >= 191) {
        rectSrc.x = 118;
    } 
    else if (y >= 182) {
        rectSrc.x = 142;
    }

    flip = (SDL_RendererFlip)(flag);
}

void ComponenteVistaMario::free() {
    SDL_DestroyTexture(texture);
}