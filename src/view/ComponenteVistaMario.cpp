#include "ComponenteVistaMario.h"
#include "../model/Mario.hpp"
#include "../logger.h"

const int TIEMPO_POR_FRAME = 5;
const int CANT_FRAMES = 3;

std::string ComponenteVistaMario::rutaImagen = "res/Mario.png";

ComponenteVistaMario::ComponenteVistaMario(SDL_Renderer *renderer) {
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load(rutaImagen.c_str());

    if(surface == NULL) {
        logger::Logger::getInstance().logError("Mario image not found: " + rutaImagen);
        logger::Logger::getInstance().logDebug("Loading Mario default image: " + IMG_DEFAULT);
        surface = IMG_Load(IMG_DEFAULT.c_str());
    } else SDL_SetColorKey(surface, SDL_TRUE, *(Uint32*)(surface->pixels));
    textura = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

}

void ComponenteVistaMario::mostrar(Uint32 frames) {
    tiempo++;

    if(tiempo >= TIEMPO_POR_FRAME * CANT_FRAMES)
    {
        tiempo = 0;
    }

    int frameActual = tiempo / TIEMPO_POR_FRAME;

    int estado = ((Mario *) mario)->getEstado();

    if(estado == REPOSO_DERECHA 
    || estado == REPOSO_IZQUIERDA) 
    {
        rectSpritesheet.x = posXTextura[0];
        rectSpritesheet.y = posYTextura;
        rectSpritesheet.w = anchoTextura;
        rectSpritesheet.h = altoTextura;

        rectRender.x = mario->posX;
        rectRender.y = mario->posY;
        rectRender.w = mario->ancho;
        rectRender.h = mario->alto;
    } 
    else if (estado == CORRIENDO_DERECHA 
    || estado == CORRIENDO_IZQUIERDA)
    {
        if((frameTextura != frameActual) || frameActual == 0)
        {
            frameTextura = frameActual;
            rectSpritesheet.x = posXTextura[frameTextura];
            rectSpritesheet.y = posYTextura;
            rectSpritesheet.w = anchoTextura;
            rectSpritesheet.h = altoTextura;

            rectRender.x = mario->posX;
            rectRender.y = mario->posY;
            rectRender.w = mario->ancho;
            rectRender.h = mario->alto;
        }
    }
    else if (estado == SALTANDO_DERECHA 
    || estado == SALTANDO_IZQUIERDA)
    {
        rectSpritesheet.x = posXTextura[3];
        rectSpritesheet.y = posYTextura;
        rectSpritesheet.w = anchoTextura;
        rectSpritesheet.h = altoTextura;

        rectRender.x = mario->posX;
        rectRender.y = mario->posY;
        rectRender.w = mario->ancho;
        rectRender.h = mario->alto;
    }

    SDL_RendererFlip flip;

    switch (estado)
    {
        case REPOSO_DERECHA:
        case CORRIENDO_DERECHA:
        case SALTANDO_DERECHA:
            flip = SDL_FLIP_HORIZONTAL;
            break;

        default:
            flip = SDL_FLIP_NONE;
            break;
    }

    //SDL_Rect rect = {mario->posX, mario->posY, mario->ancho, mario->alto};
    SDL_RenderCopyEx(renderer, textura, &rectSpritesheet, &rectRender, 0, NULL, flip);
}