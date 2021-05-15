#pragma once
#include "Entidad.h"
class ComponenteVistaEntidadEstatica {
    public:
    
    void mostrar(Entidad* entidad, std::string rutaImagen, SDL_Renderer* renderer);
    
    private:
    SDL_Texture* textura = NULL;

};