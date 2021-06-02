#include "PlataformaMovil.h"
#include "../utils/Constants.hpp"

#define MIN_X 17
#define MAX_X 191
#define MIN_Y_PLATAFORMA 124

#define INDICE_X_PLAT 58
#define INDICE_Y_PLAT 40
#define PLATAFORMAS_POR_NIVEL 3
#define VELOCIDAD_PLAT 0.25

PlataformaMovil::PlataformaMovil(int plataforma, int nivel)
: Entidad(0, 0, ANCHO_PLATAFORMA, ALTO_PLATAFORMA) {
    this->direccion = (((nivel + 1) & 2) - 1);
    int limite = ((MAX_X + MIN_X) / 2) + direccion * ((MAX_X - MIN_X) / 2);

    posX = limite - direccion * plataforma * INDICE_X_PLAT;
    posY = MIN_Y_PLATAFORMA + (nivel / 2) * INDICE_Y_PLAT + (nivel % 2) * ALTO_PLATAFORMA;
}

void PlataformaMovil::mover() {
    posX += this->direccion * VELOCIDAD_PLAT;
    posX -= this->direccion * (PLATAFORMAS_POR_NIVEL * INDICE_X_PLAT) * ((posX < MIN_X) || (posX > MAX_X));
}