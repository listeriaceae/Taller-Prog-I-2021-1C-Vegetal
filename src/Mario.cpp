#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entidad.h"
#include "Mario.h"
#include <string>
#include <iostream>

const int MAX_DESPLAZAMIENTO_PIXELES = 10;

//Maximum axis velocity of the dot
static const int MARIO_VEL = 10;

Mario::Mario(int posX, int posY, int velX, int ancho, int alto) 
: Entidad(posX, posY, ancho, alto)
{
    this->velX = velX;
    this->posXInicial = posX;
    this->posYInicial = posY;
}

void Mario::mover()
{
    posX = velX;
    // if(velX < 0 && posX < (posXInicial - MAX_DESPLAZAMIENTO_PIXELES))
    //     velX = -1 * velX; //cambio de dirección
    // if(velX > 0 && posX > (posXInicial + MAX_DESPLAZAMIENTO_PIXELES))
    //     velX = -1 * velX; //cambio de dirección
}

void Mario::mostrar(SDL_Renderer* renderer)
{
    compVista->mostrar(this, rutaImagen, renderer);
}

 //Takes key presses and adjusts the dot's velocity
void Mario::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        std::cout << "SDL_KEYDOWN ";
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: 
                std::cout << "SDLK_UP" << std::endl;
                //mVelY -= MARIO_VEL;
                break;
            case SDLK_DOWN:
                std::cout << "SDLK_DOWN" << std::endl;
                //mVelY += MARIO_VEL;
                break;
            case SDLK_LEFT:
                std::cout << "SDLK_LEFT" << std::endl;
                velX -= MARIO_VEL;
                break;
            case SDLK_RIGHT:
                std::cout << "SDLK_RIGHT" << std::endl;
                velX += MARIO_VEL;
                break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
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
                velX += MARIO_VEL;
                break;
            case SDLK_RIGHT:
                velX -= MARIO_VEL;
                break;
        }
    }
}