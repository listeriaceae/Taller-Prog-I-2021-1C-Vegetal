#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "Mario.hpp"
#include <string>
#include <iostream>

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
    // std::cout << "*** *** MOVIENDO MARIO posX i "<< posX << std::endl;
    posX += this->velX;
    // std::cout << "*** *** MOVIENDO MARIO posX f "<< posX << std::endl;
    //If the dot went too far to the left or right
    if( ( posX < 0 ) || ( posX > MAX_DESPLAZAMIENTO_X ) )
    {
        //Move back
        posX -= velX;
    }
}

void Mario::mostrar(SDL_Renderer* renderer)
{
    // std::cout << "*** MOSTRANDO MARIO" << std::endl;
    compVista->mostrar(this, rutaImagen, renderer);
}

 //Takes key presses and adjusts the dot's velocity
void Mario::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        std::cout << "KEYDOWN ";
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: 
                std::cout << "UP" << std::endl;
                //mVelY -= MARIO_VEL;
                break;
            case SDLK_DOWN:
                std::cout << "DOWN" << std::endl;
                //mVelY += MARIO_VEL;
                break;
            case SDLK_LEFT:
                std::cout << "LEFT" << std::endl;
                //velX -= MARIO_VEL;
                this->moverIzquierda();
                break;
            case SDLK_RIGHT:
                std::cout << "RIGHT" << std::endl;
                //velX += MARIO_VEL;
                this->moverDerecha();
                break;
            case SDLK_SPACE:
                std::cout << "SPACE" << std::endl;
                break;
            case SDLK_l:
                std::cout << "L" << std::endl;
                break;
            default:
                std::cout << "UNKOWN KEY" << std::endl;
                break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        std::cout << "KEYUP ";
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                //mVelY += MARIO_VEL;
                break;
            case SDLK_DOWN:
                //mVelY -= MARIO_VEL;
                break;
            case SDLK_LEFT: 
                // velX += MARIO_VEL;
                this->detenerIzquierda();
                break;
            case SDLK_RIGHT:
                // velX -= MARIO_VEL;
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