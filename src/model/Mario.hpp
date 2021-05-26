#pragma once
#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaMario.h"

enum {
    REPOSO,
    CORRIENDO,
    SALTANDO,
    TREPANDO,
    TREPANDO_REPOSO
};

class Mario : public Entidad 
{
    public: 
        Mario(float x, float y, SDL_Renderer *renderer);
        void mover();
        void mostrar();
        void setEstado(char up, char down, char left, char right);
        void getEstado(float *x, float *y, char *estado);
        void setStartPos(float x, float y);
        void saltar();
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

        void trepar(char up, char down);
        void correr(char right);
        void detener();
        void detenerTrepar();
};