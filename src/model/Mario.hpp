#pragma once
#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaMario.h"

#define SPACE 128
#define UP 8
#define DOWN 4
#define LEFT 2
#define RIGHT 1

enum {
    REPOSO,
    CORRIENDO,
    SALTANDO,
    TREPANDO
};

class Mario : public Entidad 
{
    public: 
        Mario(float x, float y, SDL_Renderer *renderer);
        void setStartPos(float x, float y);
        void mover();
        void mostrar();
        void setEstado(char controls);
        void getEstado(float *x, float *y, char *estado);
        ComponenteVistaMario* getVista();
        virtual ~Mario() {
            delete compVista;
        };

    private:
        ComponenteVistaMario* compVista;
        float velX;
        float velEnSuelo;
        float velY;
        char estado;
        char estadoEnSuelo;

        void trepar();
        void correr(char controls);
        void saltar(char controls);
};