#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "DefaultConfig.h"
#include "../view/DefaultConfigVista.h"


DefaultConfig::DefaultConfig(int posX, int posY, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    compVista = new DefaultConfigVista();
}

void DefaultConfig::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, rutaImagen, renderer);
}

void DefaultConfig::mover() {

}