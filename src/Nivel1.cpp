#include "Nivel1.h"
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel1.h"

using namespace std;

Nivel1::Nivel1(SDL_Renderer* renderer) {
    this->compVista = new ComponenteVistaNivel1(renderer);
}

void Nivel1::actualizarNivel() {
    actualizarPosicionesObjetos();
    actualizarVista();
}

void Nivel1::actualizarPosicionesObjetos() {
    std::list<Entidad*>::iterator it;
    for (it = objetos.begin(); it != objetos.end(); ++it){
        (*it)->mover();
    }
}

void Nivel1::actualizarVista() { //Por ahora solo carga el fondo
    compVista->mostrar(this);
}

void Nivel1::agregarObjeto(Entidad* objeto) {
    objetos.push_front(objeto);
}

list<Entidad*>* Nivel1::getObjetos() {
    return &objetos;
}