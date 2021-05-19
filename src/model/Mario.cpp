#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "Mario.hpp"
#include <string>
#include <iostream>
#include "../logger.h"

const int MAX_DESPLAZAMIENTO_PIXELES = 10;
const int MAX_DESPLAZAMIENTO_X = 750;

//Maximum axis velocity of Mario
static const int MARIO_VEL = 4;

Mario::Mario(int posX, int posY, int velX, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto)
{
    this->velX = velX;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->estado = REPOSO_DERECHA;
}

void Mario::mover()
{
    posX += this->velX;
    //If the dot went too far to the left or right
    if( ( posX < 0 ) || ( posX > MAX_DESPLAZAMIENTO_X ) )
    {
        //Move back
        posX -= velX;
    }
}

void Mario::mostrar(SDL_Renderer* renderer)
{
    compVista->mostrar(this, rutaImagen, renderer);
}

void Mario::handleEvent( SDL_Event& e )
{
    // If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                logger::Logger::getInstance().logDebug("event[KEYDOWN] UP");
                break;
            case SDLK_DOWN:
                logger::Logger::getInstance().logDebug("event[KEYDOWN] DOWN");
                break;
            case SDLK_LEFT:
                logger::Logger::getInstance().logDebug("event[KEYDOWN] LEFT");
                this->moverIzquierda();
                break;
            case SDLK_RIGHT:
                logger::Logger::getInstance().logDebug("event[KEYDOWN] RIGHT");
                this->moverDerecha();
                break;
            case SDLK_SPACE:
                logger::Logger::getInstance().logDebug("event[KEYDOWN] SPACE");
                break;
            default:
                logger::Logger::getInstance().logDebug("event[KEYDOWN] UNKOWN KEY");
                break;
        }
    }
    // If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                logger::Logger::getInstance().logDebug("event[KEYUP] UP");
                break;
            case SDLK_DOWN:
                logger::Logger::getInstance().logDebug("event[KEYUP] DOWN");
                break;
            case SDLK_LEFT: 
                logger::Logger::getInstance().logDebug("event[KEYUP] LEFT");
                this->detenerIzquierda();
                break;
            case SDLK_RIGHT:
                logger::Logger::getInstance().logDebug("event[KEYUP] RIGHT");
                this->detenerDerecha();
                break;
        }
    }
}

void Mario::detenerDerecha() 
{
    this->velX -= MARIO_VEL;
    this->estado = REPOSO_DERECHA;
}

void Mario::detenerIzquierda() 
{
    this->velX += MARIO_VEL;
    this->estado = REPOSO_IZQUIERDA;
}

void Mario::moverDerecha() 
{
    this->velX += MARIO_VEL;
    this->estado = CORRIENDO_DERECHA;
}

void Mario::moverIzquierda() 
{
    this->velX -= MARIO_VEL;
    this->estado = CORRIENDO_IZQUIERDA;
}

MarioEstado Mario::getEstado()
{
    return this->estado;
}