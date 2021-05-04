#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>
#include "Barril.h"

using namespace std;

Barril::Barril(int posX, int posY, int velX, int velY, string rutaImagen) {
    this->posX = posX;
    this->posY = posY;
    this->velX = velX;
    this->velY = velY;
    this->rutaImagen = rutaImagen;
}

Barril::~Barril() {
    SDL_DestroyTexture(this->imagen);
}

void Barril::inicializarImagen(SDL_Renderer* renderer) {
    surface = SDL_LoadBMP(this->rutaImagen.c_str());
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 0)); //Hace que el fondo sea transparente
    imagen = SDL_CreateTextureFromSurface(renderer, surface);
}

void Barril::mover() {
    if((SDL_GetTicks() - this->tickUltimoMovimiento) < 60) //Solo se mueve cada 60 frames
        return;
    
    posY += velY;

    if((posY < 0) || ((posY + alto) > ALTO_PANTALLA)) {
        posY -= velY;
    }

    this->tickUltimoMovimiento = SDL_GetTicks();
}

void Barril::mostrar(SDL_Renderer* renderer) {
    SDL_Rect rect = {this->posX, this->posY, ancho, alto};
    SDL_RenderCopy(renderer, this->imagen, NULL, &rect);
}

int Barril::getX() {
    return posX;
}

int Barril::getY() {
    return posY;
}