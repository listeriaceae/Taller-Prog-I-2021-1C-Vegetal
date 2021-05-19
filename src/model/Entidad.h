#pragma once
#include <SDL2/SDL.h>

class Entidad {
    public:
    int posX;
    int posY;
    int ancho;
    int alto;
    
    Entidad(int posX, int posY, int ancho, int alto);

    virtual void mostrar(SDL_Renderer* renderer) = 0;

    virtual void mover() = 0; //separar entidades en entidades estaticas y dinamicas

    private:
    

};