#pragma once
#include <string>
#include "Entidad.h"
#include "ComponenteVistaMario.h"

enum MarioEstado {
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
        Mario(int posX, int posY, int velX, int ancho, int alto);
        void mostrar(SDL_Renderer* renderer);
        void mover();
        std::string getRutaImagen();

        void handleEvent( SDL_Event& e );

        void moverDerecha();

        void moverIzquierda();

        MarioEstado getEstado();

        void detenerDerecha();

        void detenerIzquierda();

    private: 
        ComponenteVistaMario* compVista = new ComponenteVistaMario();
        
        int velX;
        int posXInicial;
        int posYInicial;
        std::string rutaImagen = "res/Mario.png";
        MarioEstado estado;
};