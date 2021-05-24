#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "DefaultConfig.h"
#include "../view/DefaultConfigVista.h"


DefaultConfig::DefaultConfig(SDL_Renderer *renderer) 
: Entidad(DEFAULT_CONFIG_X, DEFAULT_CONFIG_Y, ANCHO_DEFAULT_CONFIG, ALTO_DEFAULT_CONFIG) {
    compVista = new DefaultConfigVista(renderer);
}

void DefaultConfig::mover() {}

void DefaultConfig::mostrar() {
    compVista->mostrar();
}