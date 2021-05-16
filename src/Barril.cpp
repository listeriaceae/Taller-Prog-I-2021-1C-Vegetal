#include <string>
#include <SDL2/SDL.h>
#include "Entidad.h"
#include "Barril.h"
#include "ComponenteVistaEntidadEstatica.h"

using namespace std;

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 600;

Barril::Barril(int posX, int posY, int velX, int velY) 
: Entidad(posX, posY, 40, 40){
    this->velX = velX;
    this->velY = velY;
}

void Barril::mover() {
    if((SDL_GetTicks() - tickUltimoMovimiento) < 60) //Solo se mueve cada 60 ticks
        return;
    
    posY += velY;

    if((posY < 0) || ((posY + alto) > ALTO_PANTALLA)) {
        posY -= velY;
    }

    tickUltimoMovimiento = SDL_GetTicks();
}

void Barril::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, rutaImagen, renderer);
}