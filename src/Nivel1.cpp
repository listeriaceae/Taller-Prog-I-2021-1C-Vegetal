#include "Nivel1.h"
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "ComponenteVistaNivel1.h"
#include "Barril.h"
#include "Fuego.h"
#include "PlataformaMovil.h"
#include "EnemigoFuego.h"
#include "Peach.h"
#include "DonkeyKong.h"
#include "Polea.h"

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

void Nivel1::setFondo(std::string rutaImagen) {
    this->rutaImagen = rutaImagen;
}

void Nivel1::inicializarObjetos() {
    PlataformaMovil* m1 = new PlataformaMovil(200, 288, -4, 60, 19);
    PlataformaMovil* m2 = new PlataformaMovil(400, 307, 4, 60, 19);
    PlataformaMovil* m3 = new PlataformaMovil(250, 382, -4, 60, 19);
    PlataformaMovil* m4 = new PlataformaMovil(300, 401, 4, 60, 19);

    Fuego* f1 = new Fuego(172, 544, 56, 56);
    Fuego* f2 = new Fuego(314, 544, 56, 56);
    Fuego* f3 = new Fuego(458, 544, 56, 56);
    Fuego* f4 = new Fuego(600, 544, 56, 56);

    //Barril b1(300, 0, 0, 10);
    //Barril b2(200, 0, 0, 7);
    Polea* polea1 = new Polea(35, 300, 22, 21, "derecha");
    Polea* polea2 = new Polea(35, 394, 22, 21, "derecha");
    Polea* polea3 = new Polea(743, 300, 22, 21, "izquierda");
    Polea* polea4 = new Polea(743, 394, 22, 21, "izquierda");

    Peach* p1 = new Peach(314, 76, 40, 55);
    DonkeyKong* d1 = new DonkeyKong(129, 115, 100, 82);
    
    agregarObjeto(m1);
    agregarObjeto(m2);
    agregarObjeto(m3);
    agregarObjeto(m4);
    
    agregarObjeto(f1);
    agregarObjeto(f2);
    agregarObjeto(f3);
    agregarObjeto(f4);

    agregarObjeto(polea1);
    agregarObjeto(polea2);
    agregarObjeto(polea3);
    agregarObjeto(polea4);

    agregarObjeto(p1);
    agregarObjeto(d1);
}