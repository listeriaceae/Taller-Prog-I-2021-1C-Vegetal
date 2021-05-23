#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "Peach.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

#define PEACH_POSX 88
#define PEACH_POSY 34
#define PEACH_ANCHO 16
#define PEACH_ALTO 22

std::string Peach::rutaImagen = "res/Peach.png";

Peach::Peach(SDL_Renderer *renderer) 
: Entidad(PEACH_POSX, PEACH_POSY, PEACH_ANCHO, PEACH_ALTO) {
    SDL_Rect rect = {PEACH_POSX, PEACH_POSY, PEACH_ANCHO, PEACH_ALTO};
    compVista = new ComponenteVistaEntidadEstatica(rutaImagen, &rect, renderer);
}

void Peach::mover() {}

void Peach::mostrar(Uint32 frames) {
    compVista->mostrar(frames);
}