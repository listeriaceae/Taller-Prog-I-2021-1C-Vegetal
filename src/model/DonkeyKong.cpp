#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "DonkeyKong.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

#define DONKEYKONG_POSX 24
#define DONKEYKONG_POSY 50
#define DONKEYKONG_ANCHO 40
#define DONKEYKONG_ALTO 34

std::string DonkeyKong::rutaImagen = "res/DonkeyKong.png";

DonkeyKong::DonkeyKong(SDL_Renderer *renderer)
: Entidad(DONKEYKONG_POSX, DONKEYKONG_POSY, DONKEYKONG_ANCHO, DONKEYKONG_ALTO) {
    SDL_Rect rect = {DONKEYKONG_POSX, DONKEYKONG_POSY, DONKEYKONG_ANCHO, DONKEYKONG_ALTO};
    compVista = new ComponenteVistaEntidadEstatica(rutaImagen, &rect, renderer);
}

void DonkeyKong::mover() {}

void DonkeyKong::mostrar(Uint32 frames) {
    compVista->mostrar(frames);
}