#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "EnemigoFuego.h"
#include "ComponenteVistaEntidadEstatica.h"

const int MAX_DESPLAZAMIENTO_PIXELES = 10;
EnemigoFuego::EnemigoFuego(int posX, int posY, int velX, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    this->velX = velX;
    this->posXInicial = posX;
    this->posYInicial = posY;
}

void EnemigoFuego::mover() {
    posX += velX;
    if(velX < 0 && posX < (posXInicial - MAX_DESPLAZAMIENTO_PIXELES))
        velX = -1 * velX; //cambio de dirección
    if(velX > 0 && posX > (posXInicial + MAX_DESPLAZAMIENTO_PIXELES))
        velX = -1 * velX; //cambio de dirección
}

void EnemigoFuego::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, rutaImagen, renderer);
}