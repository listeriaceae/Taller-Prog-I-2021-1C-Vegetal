#include <string>
#include <SDL2/SDL_image.h>
#include "MarioVista.h"
#include "../logger.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define MARIO_TREPANDO_INDEX 3
#define MARIO_DE_ESPALDAS_INDEX 6
#define MARIO_SALTANDO_INDEX 14
#define MARIO_MURIENDO_INDEX 16
#define MARIO_MUERTO_INDEX 18
#define MARIO_POSE_MARTILLO_INDEX 8

#define TIEMPO_FRAME_MUERTO 16
#define TIEMPO_POR_FRAME 2
#define TIEMPO_FRAME_REPOSO_MARTILLO 8
#define TIEMPO_FRAME_CORRIENDO_MARTILLO 4
#define CANT_FRAMES 4
#define CANT_FRAMES_REPOSO_MARTILLO 2
#define MARIO_SPRITE_SIZE 24

#define POS_Y_SPRITE_MARTILLO 6
#define POS_X_SPRITE_MARTILLO_LEVANTADO 4
#define POS_X_SPRITE_MARTILLO_GOLPEANDO 16
#define POS_X_MANOS_MARIO_LEVANTANDO 4
#define POS_Y_MANOS_MARIO_GOLPEANDO 10
#define WIDTH_MARTILLO_LEVANTADO 9
#define WIDTH_MARTILLO_GOLPEANDO 16
#define HEIGHT_MARTILLO_LEVANTADO 10
#define HEIGHT_MARTILLO_GOLPEANDO 16

const std::string IMG_MARIO = "res/Mario.png";
const std::string IMG_HAMMER = "res/Hammer.png";

SDL_Renderer *MarioVista::renderer{nullptr};
SDL_Texture *MarioVista::texture{nullptr};
SDL_Texture *MarioVista::hammerTexture{nullptr};

size_t MarioVista::totalJugadores = 0;

MarioVista::MarioVista(SDL_Renderer *renderer) {
    if (texture == nullptr) {
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
    loadHammerTexture();

    srcRect.y = 0;
    srcRect.w = ANCHO_MARIO;
    srcRect.h = ALTO_MARIO;

    dstRect.w = round(ANCHO_MARIO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    dstRect.h = round(ALTO_MARIO * ALTO_PANTALLA / (float)ALTO_NIVEL);

    ++totalJugadores;
}

MarioVista::MarioVista(const MarioVista &other)
: srcRect{other.srcRect}, dstRect{other.dstRect}, flip{other.flip}, tiempo{other.tiempo} {
    ++totalJugadores;
}

void MarioVista::setColor(size_t color) {
    srcRect.y = color * ALTO_MARIO;
}

void MarioVista::mostrar(const estadoMario_t &estadoMario) {
    int nextX = round((int)estadoMario.pos.x * (ANCHO_PANTALLA / (float)ANCHO_NIVEL));
    int nextY = round((int)estadoMario.pos.y * (ANCHO_PANTALLA / (float)ANCHO_NIVEL));
    switch(estadoMario.estado) {
        case REPOSO:
        case DE_ESPALDAS:
            updateReposo(estadoMario.estado, estadoMario.hasHammer);
            break;
        case CORRIENDO:
            updateCorriendo(nextX, estadoMario.hasHammer);
            break;
        case SALTANDO:
            updateSaltando(nextX);
            break;
        case TREPANDO:
            updateTrepando(nextY);
            break;
        case MURIENDO:
        case MUERTO:
            updateMuriendo(estadoMario.estado);
            break;
        case GAME_OVER:
            return;
        default:
            break;
    }
    dstRect.x = nextX;
    dstRect.y = nextY;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0., NULL, flip);
}

void MarioVista::updateReposo(char estado, bool hasHammer) {
    if(hasHammer) {
        tiempoReposo = (tiempoReposo + 1) % (TIEMPO_FRAME_REPOSO_MARTILLO * CANT_FRAMES_REPOSO_MARTILLO);
        int frameReposo = (tiempoReposo / TIEMPO_FRAME_REPOSO_MARTILLO);
        srcRect.x = (MARIO_POSE_MARTILLO_INDEX * MARIO_SPRITE_SIZE) + frameReposo * MARIO_SPRITE_SIZE;  // 0, 1, 0, 1...
        drawHammer(frameReposo);
    } else {
        srcRect.x = (estado == DE_ESPALDAS) * (MARIO_DE_ESPALDAS_INDEX * MARIO_SPRITE_SIZE);
    }
    
}

void MarioVista::updateCorriendo(int nextX, bool hasHammer) {
    tiempo = (tiempo + (dstRect.x != nextX)) % (TIEMPO_FRAME_CORRIENDO_MARTILLO * CANT_FRAMES);
    flip = (SDL_RendererFlip)((dstRect.x < nextX) + (int)flip * (dstRect.x == nextX));
    int frameActual = (tiempo / TIEMPO_FRAME_CORRIENDO_MARTILLO);

    if(hasHammer) {
        srcRect.x = (MARIO_POSE_MARTILLO_INDEX * MARIO_SPRITE_SIZE) + frameActual * MARIO_SPRITE_SIZE;  // 0, 1, 2, 3..
        drawHammer(frameActual);
    } 
    else {
        srcRect.x = ((frameActual & 1) << ((frameActual & 2) >> 1)) * MARIO_SPRITE_SIZE;  // 0, 1, 0, 2...
    }
        
}

void MarioVista::updateSaltando(int nextX) {
    flip = (SDL_RendererFlip)((dstRect.x < nextX) + (int)flip * (dstRect.x == nextX));
    srcRect.x = MARIO_SALTANDO_INDEX * MARIO_SPRITE_SIZE;
}

void MarioVista::updateTrepando(int nextY) {
    tiempo += dstRect.y != nextY;
    flip = (SDL_RendererFlip)((tiempo / 8) % 2);
    srcRect.x = MARIO_TREPANDO_INDEX * MARIO_SPRITE_SIZE;
}

void MarioVista::updateMuriendo(char estado) {
    tiempo *= srcRect.x >= MARIO_MURIENDO_INDEX * MARIO_SPRITE_SIZE;
    ++tiempo;
    if (estado == MURIENDO) {
        int sprite = (tiempo / TIEMPO_FRAME_MUERTO) % 4;
        srcRect.x = (MARIO_MURIENDO_INDEX + 1 - sprite % 2) * MARIO_SPRITE_SIZE;
        flip = (SDL_RendererFlip)((sprite > 1) * (sprite - 1));
    }
    else {
        flip = SDL_FLIP_NONE;
        srcRect.x = MARIO_MUERTO_INDEX * MARIO_SPRITE_SIZE;
    }
}

MarioVista::~MarioVista() {
    if (--totalJugadores == 0) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void MarioVista::loadHammerTexture() {
    SDL_Surface* hammerSurface = IMG_Load(IMG_HAMMER.c_str());

    if(hammerSurface == NULL) {
        logger::Logger::getInstance().logError("Hammer image not found: " + IMG_HAMMER);
        logger::Logger::getInstance().logDebug("Loading hammer default image: " + IMG_DEFAULT);
        hammerSurface = IMG_Load(IMG_DEFAULT.c_str());
    } else SDL_SetColorKey(hammerSurface, SDL_TRUE, *(Uint32*)(hammerSurface->pixels));
    hammerTexture = SDL_CreateTextureFromSurface(renderer, hammerSurface);
    SDL_FreeSurface(hammerSurface);

    hammerSrc.x = POS_X_SPRITE_MARTILLO_LEVANTADO;
    hammerSrc.y = POS_Y_SPRITE_MARTILLO;
    hammerSrc.w = WIDTH_MARTILLO_LEVANTADO;
    hammerSrc.h = HEIGHT_MARTILLO_LEVANTADO;

    hammerDst.w = round((float)WIDTH_MARTILLO_LEVANTADO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
    hammerDst.h = round((float)HEIGHT_MARTILLO_LEVANTADO * ALTO_PANTALLA / (float)ALTO_NIVEL);
}

void MarioVista::drawHammer(int frame) {
    SDL_RendererFlip hammerFlip = flip;

    if(frame % 2 == 0) { //Mario levantando el martillo
        hammerDst.w = round((float)WIDTH_MARTILLO_LEVANTADO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
        hammerSrc.w = WIDTH_MARTILLO_LEVANTADO;
        hammerSrc.x = POS_X_SPRITE_MARTILLO_LEVANTADO;
        hammerDst.x = dstRect.x + round(POS_X_SPRITE_MARTILLO_LEVANTADO * ANCHO_PANTALLA / (float)ANCHO_NIVEL); //pos_x martillo = pos mario + pos martillo
        hammerDst.y = dstRect.y - hammerDst.h; //pos_y martillo = pos mario - alto martillo
    } else if((frame % 2 == 1)) { //Mario golpeando con el martillo
        hammerDst.w = round((float)WIDTH_MARTILLO_GOLPEANDO * ANCHO_PANTALLA / (float)ANCHO_NIVEL);
        hammerSrc.w = WIDTH_MARTILLO_GOLPEANDO;
        hammerSrc.x = POS_X_SPRITE_MARTILLO_GOLPEANDO;
        if(flip == SDL_FLIP_HORIZONTAL) { //La posicion del martillo cambia respecto hacia donde esta mirando mario
            hammerDst.x = dstRect.x + dstRect.w;
        } else {
            hammerDst.x = dstRect.x - hammerDst.w;
        }
        hammerDst.y = dstRect.y + round(((float)ALTO_MARIO - (float)POS_Y_MANOS_MARIO_GOLPEANDO) * ALTO_PANTALLA / (float)ALTO_NIVEL); //
    }

    SDL_RenderCopyEx(renderer, hammerTexture, &hammerSrc, &hammerDst, 0., NULL, hammerFlip);
}