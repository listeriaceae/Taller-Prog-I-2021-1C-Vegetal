#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Entidad.h"
#include "FireBarrel.h"
#include "ComponenteVistaEntidadEstatica.h"

FireBarrel::FireBarrel(int posX, int posY, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    compVista = new ComponenteVistaEntidadEstatica();
}

void FireBarrel::mostrar(SDL_Renderer* renderer) {

    compVista->mostrar(this, rutaImagen, renderer);
}
void FireBarrel::mover() {

}