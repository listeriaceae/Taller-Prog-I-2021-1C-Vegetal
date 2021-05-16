#pragma once
#include <SDL2/SDL.h>
class Nivel1;

class ComponenteVistaNivel1 {
    public:
    
    ComponenteVistaNivel1(SDL_Renderer* renderer);
    void mostrar(Nivel1* nivel1);
    
    private:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* textura = NULL;

    void mostrarFondo(Nivel1* nivel1);
    void mostrarObjetos(Nivel1* nivel1);
};