#pragma once
#include <SDL2/SDL.h>

class Entidad {
    public:

        float posX;
        float posY;
        int ancho;
        int alto;
    
        Entidad(float posX, float posY, int ancho, int alto);
        virtual void mostrar(Uint32 frames) = 0;
        virtual void mover() = 0; //separar entidades en entidades estaticas y dinamicas
    protected:
        ~Entidad() = default;

    private:
};