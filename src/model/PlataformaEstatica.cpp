#include <stdlib.h>
#include "PlataformaEstatica.h"
#include "Coordenada.h"

PlataformaEstatica::PlataformaEstatica(Coordenada extremo1, Coordenada extremo2)
 : extremo1(extremo1), extremo2(extremo2) {
    this->extremo1 = extremo1;
    this->extremo2 = extremo2;
}

Coordenada PlataformaEstatica::getPosicionAleatoria() {
    int xAleatoria, yAleatoria;

    xAleatoria = extremo1.getX() + rand() % (extremo2.getX() - extremo1.getX());
    yAleatoria = getY(xAleatoria);

    Coordenada coordAleatoria(xAleatoria, yAleatoria);

    return coordAleatoria;
}

int PlataformaEstatica::getY(int x) {
    float y1 = (float)extremo1.getY();
    float y2 = (float)extremo2.getY();
    float x1 = (float)extremo1.getX();
    float x2 = (float)extremo2.getX();

    float y = y1 + x * (y2 - y1) / (x2 - x1);
    
    return (int)y;
}
