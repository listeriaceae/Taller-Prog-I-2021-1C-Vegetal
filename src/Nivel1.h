#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ComponenteVistaNivel1.h"

class Nivel1 {
    public:
    std::string rutaImagen = "res/Nivel1.png";

    Nivel1(SDL_Renderer* renderer);
    void actualizarVista();

    private:
    ComponenteVistaNivel1* compVista = NULL;
};