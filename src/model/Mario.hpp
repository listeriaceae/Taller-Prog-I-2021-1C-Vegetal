#pragma once
#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaMario.h"

enum {
    REPOSO,
    CORRIENDO,
    SALTANDO,
    ESCALANDO
};

class Mario : public Entidad 
{
    public: 
        Mario(int posX, int posY, int ancho, int alto);
        void mover();
        void mostrar(Uint32 frames);
        void set_estado(char up, char down, char left, char right);

        void saltar();
        int getEstado();

    private:
        ComponenteVistaMario* compVista = new ComponenteVistaMario();
        char velX;
        char velEnSuelo;
        float velY;
        char estado;
        char enstadoEnSuelo;
        char sentido;
        char sentidoEnSuelo;

        void trepar(char up);
        void caminar(char right);
        void detener();
};