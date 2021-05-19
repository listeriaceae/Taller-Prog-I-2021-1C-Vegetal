#pragma once
#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaMario.h"

enum {
    REPOSO_DERECHA,
    REPOSO_IZQUIERDA,
    CORRIENDO_DERECHA,
    CORRIENDO_IZQUIERDA,
    SALTANDO_DERECHA,
    SALTANDO_IZQUIERDA,
    ESCALANDO
};

class Mario : public Entidad 
{
    public: 
        Mario(int posX, int posY, int ancho, int alto);
        void mostrar(SDL_Renderer* renderer);
        void mover();
        std::string getRutaImagen();

        void handleEvent( SDL_Event& e );

        void moverDerecha();

        void moverIzquierda();

        int getEstado();

        void detenerDerecha();

        void detenerIzquierda();

        void saltar();

    private: 
        ComponenteVistaMario* compVista = new ComponenteVistaMario();
        int velX;
        int velEnSuelo;
        float velY;
        int posXInicial;
        int posYInicial;
        float marioPosY;
        std::string rutaImagen = "res/Mario.png";
        int estado;
};