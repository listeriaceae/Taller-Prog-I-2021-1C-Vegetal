#include "PlataformaMovil.h"

#define MIN_X 17
#define MAX_X 191
#define MIN_Y_PLATAFORMA 124

#define INDICE_X_PLAT 58
#define INDICE_Y_PLAT 40
#define PLATAFORMAS_POR_NIVEL 3
#define VELOCIDAD_PLAT 0.25

PlataformaMovil::PlataformaMovil(int plataforma, int nivel, SDL_Renderer *renderer)
: Entidad(0, 0, ANCHO_PLATAFORMA, ALTO_PLATAFORMA) {
    this->direccion = (((nivel + 1) & 2) - 1);
    this->limite = ((MAX_X + MIN_X) >> 1) + direccion * ((MAX_X - MIN_X) >> 1);

    posX = this->limite - direccion * plataforma * INDICE_X_PLAT;
    posY = MIN_Y_PLATAFORMA + (nivel >> 1) * INDICE_Y_PLAT + (nivel & 1) * ALTO_PLATAFORMA;

    compVista = new ComponenteVistaPlataformaMovil(posY, renderer);
}

void PlataformaMovil::mover() {
    posX += this->direccion * VELOCIDAD_PLAT;
    posX -= this->direccion * PLATAFORMAS_POR_NIVEL * INDICE_X_PLAT * ((posX * this->direccion) > (this->limite * this->direccion));
}

void PlataformaMovil::mostrar() {
    compVista->mover(posX);
    compVista->mostrar();
}