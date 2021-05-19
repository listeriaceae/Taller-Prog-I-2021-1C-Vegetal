#include "Polea.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ComponenteVistaPolea.h"

Polea::Polea(int posX, int posY, int ancho, int alto, std::string direccion) 
: Entidad(posX, posY, ancho, alto){
    compVista = new ComponenteVistaPolea(direccion);
}

void Polea::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, renderer);
}

void Polea::mover() {
    
}