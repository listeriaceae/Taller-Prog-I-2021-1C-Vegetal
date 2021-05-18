#include "Fuego.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ComponenteVistaFuego.h"

Fuego::Fuego(int posX, int posY, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    compVista = new ComponenteVistaFuego();
}

void Fuego::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, renderer);
}

void Fuego::mover() {
    
}