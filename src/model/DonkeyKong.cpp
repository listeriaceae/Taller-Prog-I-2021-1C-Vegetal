#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "DonkeyKong.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

DonkeyKong::DonkeyKong(int posX, int posY, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    compVista = new ComponenteVistaEntidadEstatica();
}

void DonkeyKong::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, rutaImagen, renderer);
}
void DonkeyKong::mover() {

}