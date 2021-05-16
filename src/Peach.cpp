#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "Peach.h"
#include "ComponenteVistaEntidadEstatica.h"

Peach::Peach(int posX, int posY, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    compVista = new ComponenteVistaEntidadEstatica();
}

void Peach::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, rutaImagen, renderer);
}