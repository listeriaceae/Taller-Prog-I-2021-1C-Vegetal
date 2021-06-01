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
#include "Coordenada.h"

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
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(88, 56), Coordenada(126, 56)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(24, 84),Coordenada(144, 84)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(160, 87), Coordenada(192, 87)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(208, 88), Coordenada(240, 88)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(0, 120), Coordenada(16, 120)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(208, 120), Coordenada(224, 120)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(0, 160), Coordenada(16, 160)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(208, 160), Coordenada(224, 160)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(0, 200), Coordenada(48, 200)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(64, 200), Coordenada(88, 200)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(104, 200), Coordenada(128, 200)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(144, 200), Coordenada(168, 200)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(184, 200), Coordenada(224, 200)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(0, 248), Coordenada(48, 248)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(64, 248), Coordenada(88, 248)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(104, 248), Coordenada(128, 248)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(144, 248), Coordenada(168, 248)));
    this->plataformasEstaticas.push_back(new PlataformaEstatica(Coordenada(184, 248), Coordenada(224, 248)));
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

Coordenada Nivel1::getPosicionAleatoria() {
    int numeroPlataformaAleatoria = rand() % plataformasEstaticas.size();
    PlataformaEstatica* plataforma = this->plataformasEstaticas[numeroPlataformaAleatoria];
    Coordenada posicionAleatoria = plataforma->getPosicionAleatoria();

    return posicionAleatoria;
}