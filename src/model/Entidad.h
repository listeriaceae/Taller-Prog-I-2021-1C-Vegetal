#pragma once

struct punto
{
    float x = 0.f;
    float y = 0.f;
};

typedef struct punto punto_t;

class Entidad {
    public:
        Entidad(float posX, float posY, int ancho, int alto);
        virtual void mover() = 0; //separar entidades en entidades estaticas y dinamicas
        punto_t getPos();
        virtual ~Entidad() = default;

    protected:
        float posX;
        float posY;
        int ancho;
        int alto;

};