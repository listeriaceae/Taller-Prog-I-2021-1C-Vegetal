#pragma once
#include <list>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ComponenteVistaNivel1.h"
#include "Entidad.h"
#include "NivelBase.h"
#include "PlataformaEstatica.h"

struct punto_t {
  int x;
  int y;
};

class Nivel1 : public NivelBase 
{
    public:
        std::string rutaImagen = "res/default.png";

    Nivel1(SDL_Renderer* renderer, bool useDefaultConfig);
    void actualizarNivel();
    void agregarObjeto(Entidad* objeto);
    void setFondo(std::string rutaImagen);
    void inicializarObjetos();
    std::list<Entidad*>* getObjetos();
    punto_t getPosicionAleatoria();

    private:
    ComponenteVistaNivel1* compVista = NULL;
    std::vector<PlataformaEstatica*> plataformasEstaticas;
    std::list<Entidad*> objetos;

    void inicializarPlataformasEstaticas();
    void actualizarVista();
    void actualizarPosicionesObjetos();
};