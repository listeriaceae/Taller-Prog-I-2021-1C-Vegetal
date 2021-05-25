#include <stdlib.h>
#include "Nivel1.h"
#include "PlataformaMovil.h"
#include "Fuego.h"
#include "Peach.h"
#include "DonkeyKong.h"
#include "Polea.h"
#include "PlataformaEstatica.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"
#include "DefaultConfig.h"
#include "../utils/Constants.hpp"
#include "../logger.h"

using namespace std;

std::string Nivel1::rutaImagen = IMG_DEFAULT;

Nivel1::Nivel1(SDL_Renderer* renderer, bool useDefaultConfig) {
    this->compVista = new ComponenteVistaNivel(renderer, rutaImagen);
    this->useDefaultConfig = useDefaultConfig;
}

void Nivel1::actualizarNivel() {
    std::list<Entidad*>::iterator it;
    for (it = objetos.begin(); it != objetos.end(); ++it) (*it)->mover();
}

void Nivel1::actualizarVista() {
    compVista->mostrar(&objetos);
    
}

void Nivel1::agregarObjeto(Entidad* objeto) {
    objetos.push_front(objeto);
}

list<Entidad*>* Nivel1::getObjetos() {
    return &objetos;
}

void Nivel1::setFondo(std::string rutaImagen) {
    compVista->setFondo(rutaImagen);
}
void Nivel1::inicializarPlataformasEstaticas() {
    this->plataformasEstaticas.push_back(new PlataformaEstatica(88, 56, 48, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(24, 84, 120, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(160, 87, 32, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(208, 88, 16, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(0, 120, 16, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(208, 120, 16, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(0, 160, 16, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(208, 160, 16, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(0, 200, 48, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(64, 200, 24, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(104, 200, 24, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(144, 200, 24, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(184, 200, 40, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(0, 248, 48, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(64, 248, 24, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(104, 248, 24, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(144, 248, 24, 8));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(184, 248, 40, 8));
}

void Nivel1::inicializarObjetos(SDL_Renderer* renderer) {
    inicializarPlataformasEstaticas();

    agregarObjeto(new PlataformaMovil(0, 0, renderer));
    agregarObjeto(new PlataformaMovil(1, 0, renderer));
    agregarObjeto(new PlataformaMovil(2, 0, renderer));

    agregarObjeto(new PlataformaMovil(0, 1, renderer));
    agregarObjeto(new PlataformaMovil(1, 1, renderer));
    agregarObjeto(new PlataformaMovil(2, 1, renderer));

    agregarObjeto(new PlataformaMovil(0, 2, renderer));
    agregarObjeto(new PlataformaMovil(1, 2, renderer));
    agregarObjeto(new PlataformaMovil(2, 2, renderer));

    agregarObjeto(new PlataformaMovil(0, 3, renderer));
    agregarObjeto(new PlataformaMovil(1, 3, renderer));
    agregarObjeto(new PlataformaMovil(2, 3, renderer));

    agregarObjeto(new Polea(N1_POSX1_POLEA, N1_POSY1_POLEA, 0, 0, renderer));
    agregarObjeto(new Polea(N1_POSX2_POLEA, N1_POSY1_POLEA, 1, 0, renderer));
    agregarObjeto(new Polea(N1_POSX1_POLEA, N1_POSY2_POLEA, 0, 1, renderer));
    agregarObjeto(new Polea(N1_POSX2_POLEA, N1_POSY2_POLEA, 1, 1, renderer));

    agregarObjeto(new Fuego(N1_POSX_FUEGO1, N1_POSY_FUEGO, renderer));
    agregarObjeto(new Fuego(N1_POSX_FUEGO2, N1_POSY_FUEGO, renderer));
    agregarObjeto(new Fuego(N1_POSX_FUEGO3, N1_POSY_FUEGO, renderer));
    agregarObjeto(new Fuego(N1_POSX_FUEGO4, N1_POSY_FUEGO, renderer));

    agregarObjeto(new Peach(renderer));
    agregarObjeto(new DonkeyKong(renderer));

    if(this->getDefaultConfigFlag()) {
        agregarObjeto(new DefaultConfig(renderer));
    }
}

punto_t Nivel1::getPosicionAleatoria() {
    int numeroPlataformaAleatoria = rand() % plataformasEstaticas.size();
    PlataformaEstatica* plataforma = this->plataformasEstaticas[numeroPlataformaAleatoria];
    int posXAleatoria = plataforma->posX + rand() % (plataforma->ancho );
    int posYAleatoria = plataforma->posY;

    punto_t posAleatoria;
    posAleatoria.x = (float)posXAleatoria;
    posAleatoria.y = (float)posYAleatoria;

    return posAleatoria;
}