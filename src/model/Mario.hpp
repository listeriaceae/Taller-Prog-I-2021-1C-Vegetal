#pragma once
#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaMario.h"

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
        void mover();
        void mostrar(Uint32 frames);
        void setEstado(char up, char down, char left, char right);
        void getEstado(float *x, float *y, char *estado);
        void setStartPos(float x, float y);
        void saltar();
        void free();

    private:
        ComponenteVistaMario* compVista;
        float velX;
        float velEnSuelo;
        float velY;
        char estado;
        char estadoEnSuelo;

        void trepar();
        void caminar(char right);
        void detener();
};