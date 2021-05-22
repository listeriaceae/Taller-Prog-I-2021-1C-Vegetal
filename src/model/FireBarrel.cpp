#include "FireBarrel.h"

#define POSX_BARRIL 3
#define POSY_BARRIL 246
#define ANCHO_BARRIL 16
#define ALTO_BARRIL 16

std::string FireBarrel::rutaImagen = "res/FireBarrel.png";

FireBarrel::FireBarrel(SDL_Renderer* renderer) 
: Entidad(POSX_BARRIL, POSY_BARRIL, ANCHO_BARRIL, ALTO_BARRIL) {
    SDL_Rect rect = {POSX_BARRIL, POSY_BARRIL, ANCHO_BARRIL, ALTO_BARRIL};
    compVista = new ComponenteVistaEntidadEstatica(rutaImagen, rect, renderer);
}

void FireBarrel::mostrar() {
    compVista->mostrar();
}

void FireBarrel::mover() {}