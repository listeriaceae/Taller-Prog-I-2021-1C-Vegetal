#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "Mario.h"

const int MAX_DESPLAZAMIENTO_PIXELES = 10;

Mario::Mario(int posX, int posY, int velX, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto)
{
    this->velX = velX;
    this->posXInicial = posX;
    this->posYInicial = posY;
}

void Mario::mover()
{
    posX += velX;
    if(velX < 0 && posX < (posXInicial - MAX_DESPLAZAMIENTO_PIXELES))
        velX = -1 * velX; //cambio de dirección
    if(velX > 0 && posX > (posXInicial + MAX_DESPLAZAMIENTO_PIXELES))
        velX = -1 * velX; //cambio de dirección
}

void Mario::mostrar(SDL_Renderer* renderer)
{
    compVista->mostrar(this, rutaImagen, renderer);
}