#pragma once

#include <string>
#include "../model/Entidad.h"


class ComponenteVistaMario 
{
    public:
        void mostrar(Uint32 frames);

    private:
        static SDL_Renderer *renderer;
        SDL_Texture* textura = NULL;
        SDL_Rect rectSpritesheet; //Rectangulo que determina que parte de la imagen cargar
        SDL_Rect rectRender; //Rectangulo que determina donde se va a renderear el objeto
        int frameTextura = 0;
        int tiempo = 0;
        int posXTextura[4] = {0, 24, 46, 337};
        int posYTextura = 0;
        int anchoTextura = 16;
        int altoTextura = 16;
        std::string rutaImagen;
};