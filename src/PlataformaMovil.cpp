#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "PlataformaMovil.h"
#include "ComponenteVistaEntidadEstatica.h"

PlataformaMovil::PlataformaMovil(int posX, int posY, int velX, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    this->velX = velX;
}

void PlataformaMovil::mover() {
    if(posX <= 56) {
        posX = 57;
        posY += 19;
        velX = 4;
    } else if(posX >= (743 - ancho)) {
        posX = 742 - ancho;
        posY -= 19;
        velX = -4;
    }
    else {
        posX += velX;
    }
}

void PlataformaMovil::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, rutaImagen, renderer);
}