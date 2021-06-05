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
: Plataforma(0, 0, 0, 0) {
    this->direccion = (((nivel + 1) & 2) - 1);
    int limite = ((MAX_X + MIN_X) / 2) + direccion * ((MAX_X - MIN_X) / 2);

    extremo1.x = limite - direccion * plataforma * INDICE_X_PLAT;
    extremo1.y = MIN_Y_PLATAFORMA + (nivel / 2) * INDICE_Y_PLAT + (nivel % 2) * ALTO_PLATAFORMA;
    extremo2.x = extremo1.x + ANCHO_PLATAFORMA;
    extremo2.y = extremo1.y;
}

void PlataformaMovil::mover() {
    extremo1.x += this->direccion * VELOCIDAD_PLAT;
    extremo1.x -= this->direccion * (PLATAFORMAS_POR_NIVEL * INDICE_X_PLAT) * ((extremo1.x < MIN_X) || (extremo1.x > MAX_X));
    extremo2.x = extremo1.x + ANCHO_PLATAFORMA;
}

punto_t PlataformaMovil::getPos() {
    return extremo1;
}