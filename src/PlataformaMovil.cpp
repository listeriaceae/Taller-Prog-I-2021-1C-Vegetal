#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "PlataformaMovil.h"
#include "Rendereable.h"
#include "ComponenteVistaEntidadEstatica.h"

const int LIMITE_IZQ = 56;
const int LIMITE_DER = 743;
const int DESPLAZAMIENTO_VERTICAL = 19;
PlataformaMovil::PlataformaMovil(int posX, int posY, int velX, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto){
    this->velX = velX;
}

void PlataformaMovil::mover() {
    if(posX <= LIMITE_IZQ) {
        posX = LIMITE_IZQ + 1;
        posY += DESPLAZAMIENTO_VERTICAL;
        velX = -velX;
    } else if(posX >= (LIMITE_DER - ancho)) {
        posX = LIMITE_DER - 1 - ancho;
        posY -= DESPLAZAMIENTO_VERTICAL;
        velX = -velX;
    }
    else {
        posX += velX;
    }
}

void PlataformaMovil::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(this, rutaImagen, renderer);
}