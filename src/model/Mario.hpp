#pragma once
#include "Entidad.h"
#include "../view/MarioVista.h"

#define SPACE 128
#define UP 8
#define DOWN 4
#define LEFT 2
#define RIGHT 1

struct estadoMario {
    punto_t pos;
    char estado;
};

typedef struct estadoMario estadoMario_t;

class Mario : public Entidad 
{
    public: 
        Mario();
        void setStartPos(float x, float y);
        void mover();
        void setEstado(char controls);
        estadoMario_t getEstado();
        MarioVista* getVista(SDL_Renderer *renderer);

    private:
        float velX;
        float velEnSuelo;
        float velY;
        char estado;
        char estadoEnSuelo;

        void trepar();
        void correr(char controls);
        void saltar(char controls);
};