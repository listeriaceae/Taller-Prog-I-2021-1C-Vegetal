#include <string>
#include <SDL2/SDL_image.h>
#include "MarioVista.h"
#include "../logger.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define MARIO_SPRITE_INDEX_SIZE 24
#define MARIO_SALTO_INDEX 14
#define TIEMPO_POR_FRAME 4
#define CANT_FRAMES 4

const std::string IMG_MARIO = "res/Mario.png";

SDL_Renderer *MarioVista::renderer = NULL;
SDL_Texture *MarioVista::texture = NULL;
SDL_Rect MarioVista::dstRect;
int MarioVista::totalJugadores = 0;

MarioVista::MarioVista(SDL_Renderer *renderer) {
    if (texture == NULL) {
        this->renderer = renderer;
        SDL_Surface* surface = IMG_Load(IMG_MARIO.c_str());

        if(surface == NULL) {
            logger::Logger::getInstance().logError("Mario image not found: " + IMG_MARIO);
            logger::Logger::getInstance().logDebug("Loading Mario default image: " + IMG_DEFAULT);
            surface = IMG_Load(IMG_DEFAULT.c_str());
        } else SDL_SetColorKey(surface, SDL_TRUE, *(Uint32*)(surface->pixels));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    srcRect.y = 0;
    srcRect.w = ANCHO_MARIO;
    srcRect.h = ALTO_MARIO;

    dstRect.w = round(ANCHO_MARIO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    dstRect.h = round(ALTO_MARIO * ALTO_PANTALLA / (float)ALTO_NIVEL);

    tiempo = 0;
    flip = SDL_FLIP_HORIZONTAL;

    ++totalJugadores;
}

void MarioVista::setColor(int nroJugador) {
    srcRect.y = nroJugador * ALTO_MARIO;
}

void MarioVista::mostrar(punto_t pos, char estado) {

    int nextX = round(pos.x * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    switch(estado) {
        case REPOSO:
            updateReposo();
            break;
        case CORRIENDO:
            updateCorriendo(nextX);
            break;
        case SALTANDO:
            updateSaltando(nextX);
            break;
        case TREPANDO:
            updateTrepando(pos);
            break;
        default:
            break;
    }
    dstRect.x = nextX;
    dstRect.y = round(pos.y * ALTO_PANTALLA / (float)ALTO_NIVEL);

    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0., NULL, flip);
}

void MarioVista::updateReposo() {
    srcRect.x = 0;
}

void MarioVista::updateCorriendo(int nextX) {
    tiempo = (tiempo + 1) % (TIEMPO_POR_FRAME * CANT_FRAMES);
    flip = (SDL_RendererFlip)((dstRect.x < nextX) + (int)flip * (dstRect.x == nextX));
    int frameActual = (tiempo / TIEMPO_POR_FRAME);
    srcRect.x = ((frameActual & 1) << ((frameActual & 2) >> 1)) * MARIO_SPRITE_INDEX_SIZE;  // 0, 1, 0, 2...
}

void MarioVista::updateSaltando(int nextX) {
    flip = (SDL_RendererFlip)((dstRect.x < nextX) + (int)flip * (dstRect.x == nextX));
    srcRect.x = MARIO_SALTO_INDEX * MARIO_SPRITE_INDEX_SIZE;
}

void MarioVista::updateTrepando(punto_t pos) {
    // TREPANDO
    // La imagen de Mario de espaldas es mas ancha que la de perfil
    srcRect.h = ALTO_MARIO;
    srcRect.w = ANCHO_MARIO;
    srcRect.x = 72; // Escalar 1

    bool flag = true;
    if (pos.y >= 232){
        srcRect.x = 142;
    }
    else if (pos.y >= 229) // 1 escalon
        flag = true;
    else if (pos.y >= 225) // 2 escalon
        flag = false;
    else if (pos.y >= 221) // 3
        flag = true;
    else if (pos.y >= 217) // 4
        flag = false;
    else if (pos.y >= 213) // 5
        flag = true;
    else if (pos.y >= 209) // 6
        flag = false;
    else if (pos.y >= 205) // 7
        flag = true;
    else if (pos.y >= 201) // 8
        flag = false;
    else if (pos.y >= 197) // 9
        flag = true;
    else if (pos.y >= 193) {
        srcRect.x = 95; // Escalar 2
    } else if (pos.y >= 191) {
        srcRect.x = 118; // Escalar 3
    } else if (pos.y >= 188)
        flag = false;
    else {
        srcRect.w = 17;
        srcRect.x = 142;
    } 

    flip = (SDL_RendererFlip)(flag);
}

MarioVista::~MarioVista() {
    if (--totalJugadores == 0) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}