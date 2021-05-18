#pragma once
#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel1.h"
#include "Entidad.h"

class Nivel1 {
    public:
    std::string rutaImagen = "res/Nivel1.png";

    Nivel1(SDL_Renderer* renderer);
    void actualizarNivel();
    void agregarObjeto(Entidad* objeto);
    std::list<Entidad*>* getObjetos();

    private:
    ComponenteVistaNivel1* compVista = NULL;
    std::list<Entidad*> objetos;

    void actualizarVista();
    void actualizarPosicionesObjetos();
};