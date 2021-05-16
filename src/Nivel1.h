#pragma once
#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel1.h"
#include "Rendereable.h"
class Nivel1 {
    public:
    std::string rutaImagen = "res/Nivel1.png";

    Nivel1(SDL_Renderer* renderer);
    void actualizarVista();
    void agregarObjeto(Rendereable* objeto);
    std::list<Rendereable*>* getObjetos();

    private:
    ComponenteVistaNivel1* compVista = NULL;
    std::list<Rendereable*> objetos;
};