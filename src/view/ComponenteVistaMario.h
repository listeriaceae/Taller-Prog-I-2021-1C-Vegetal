#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "../model/Entidad.h"


class ComponenteVistaMario 
{
    public:
        void mostrar(Entidad* entidad, std::string rutaImagen, SDL_Renderer* renderer);

    private:
        SDL_Texture* textura = NULL;
        SDL_Rect rectSpritesheet; //Rectangulo que determina que parte de la imagen cargar
        SDL_Rect rectRender; //Rectangulo que determina donde se va a renderear el objeto
        int frameTextura = 0;
        int tiempo = 0;
        int posXTextura[4] = {0, 24, 46, 337};
        int posYTextura = 0;
        int anchoTextura = 16;
        int altoTextura = 16;
};