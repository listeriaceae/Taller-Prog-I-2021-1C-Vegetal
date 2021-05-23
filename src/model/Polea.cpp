#include "Polea.h"

Polea::Polea(int x, int y, int direccion, SDL_Renderer *renderer) 
: Entidad(x, y, ANCHO_POLEA, ALTO_POLEA){
    compVista = new ComponenteVistaPolea(x, y, direccion, renderer);
}

void Polea::mover() {}

void Polea::mostrar(Uint32 frames) {
    compVista->mostrar(frames);
}