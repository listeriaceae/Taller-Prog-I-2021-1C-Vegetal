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
static const int MARIO_VELX = 4;
static const int MARIO_VEL_SALTO = 4;
static const float MARIO_ACC = -0.2;

Mario::Mario(int posX, int posY, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto)
{
    this->velX = 0;
    this->velEnSuelo = 0;
    this->velY = 0.;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->marioPosY = posY;
    this->estado = REPOSO_DERECHA;
}

void Mario::mover()
{
    this->marioPosY -= this->velY;
    this->velY += MARIO_ACC * (this->estado == SALTANDO_IZQUIERDA || this->estado == SALTANDO_DERECHA);
    if (this->marioPosY > this->posYInicial) {
        this->velX = this->velEnSuelo;
        this->estado = this->enstadoEnSuelo;
        this->marioPosY = posYInicial;
        this->velY = 0.;
    }
    posY = round(this->marioPosY);
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
                this->saltar();
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
    this->velEnSuelo -= MARIO_VELX;
    this->enstadoEnSuelo = REPOSO_DERECHA;
    if (!this->velY) {
    this->velX -= MARIO_VELX;
    this->estado = REPOSO_DERECHA;
    }
}

void Mario::detenerIzquierda() 
{
    this->velEnSuelo += MARIO_VELX;
    this->enstadoEnSuelo = REPOSO_IZQUIERDA;
    if (!this->velY) {
    this->velX += MARIO_VELX;
    this->estado = REPOSO_IZQUIERDA;
    }
}

void Mario::moverDerecha() 
{
    this->velEnSuelo += MARIO_VELX;
    this->enstadoEnSuelo = CORRIENDO_DERECHA;
    if (!this->velY) {
    this->velX += MARIO_VELX;
    this->estado = CORRIENDO_DERECHA;
    }
}

void Mario::moverIzquierda() 
{
    this->velEnSuelo -= MARIO_VELX;
    this->enstadoEnSuelo = CORRIENDO_IZQUIERDA;
    if (!this->velY) {
    this->velX -= MARIO_VELX;
    this->estado = CORRIENDO_IZQUIERDA;
    }
}

void Mario::saltar()
{
    if (this->velY) return;
    this->velY = MARIO_VEL_SALTO;
    this->estado = SALTANDO_DERECHA + (estado % 2);
}

int Mario::getEstado()
{
    return this->estado;
}