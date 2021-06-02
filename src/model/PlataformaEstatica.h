#pragma once
#include "Coordenada.h"

class PlataformaEstatica {
    public:
    PlataformaEstatica(Coordenada extremo1, Coordenada extremo2);
    Coordenada getPosicionAleatoria();
    private:
    Coordenada extremo1;
    Coordenada extremo2;
    int getY(int x);
};