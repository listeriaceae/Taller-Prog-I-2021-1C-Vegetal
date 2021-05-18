#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include "Entidad.h"
#include "Nivel1.h"
#include "Barril.h"
#include "Fuego.h"
#include "PlataformaMovil.h"
#include "EnemigoFuego.h"
#include "Peach.h"
#include "Mario.hpp"
#include <string>
#include "DonkeyKong.h"
#include "configuration.hpp"
#include "logger.h"

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 600;
const int FRAMES_POR_SEG = 60;

const std::string NOMBRE_JUEGO = "Donkey Kong 2 Jumpman Returns";

int main(void)
{
    auto configuration = configuration::Configuration("archivo.json");
    auto log_level = configuration.getLogLevel();
    logger::Logger::getInstance().setDebugLevel(log_level);

    logger::Logger::getInstance().logNewGame();

    // TODO: Handle errors...
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(NOMBRE_JUEGO.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Init(SDL_INIT_VIDEO);
    bool terminarPrograma = false;

    SDL_Event event;
    
    Nivel1 n1(renderer);

    Mario mario(3, 529, 0, 56, 56);
    n1.agregarObjeto(&mario);

    logger::Logger::getInstance().logInformation("Log level = " + log_level);

    auto enemies = configuration.getEnemies();
    for (auto enemy: enemies)
    {
        if(enemy.getType().compare("Fuego") == 0) {
            for(unsigned int i = 0; i < enemy.getQuantity(); i++) {
                int posX = rand() % (ANCHO_PANTALLA - 32);
                int posY = rand() % (ALTO_PANTALLA - 32);
                int numRandom = (rand() % 2);
                int velX;
                if(numRandom == 0)
                    velX = -1;
                else
                    velX = 1;
                EnemigoFuego* fuego = new EnemigoFuego(posX, posY, velX, 32, 32);
                n1.agregarObjeto(fuego);
            }
        }
        logger::Logger::getInstance().logDebug("Enemy type = " + enemy.getType());
        logger::Logger::getInstance().logDebug("Enemy quantity = " + enemy.getQuantity());
    }
    
    auto stages = configuration.getStages();
    for (unsigned int i = 0; i < stages.size(); ++i)
    {
        if(i == 0) {
            logger::Logger::getInstance().logDebug("Stage 1 background img = " + stages[i].getBackgrounds()[0]);
            n1.setFondo(stages[i].getBackgrounds()[0]);
        }
    }

    n1.inicializarObjetos();
    
    while(!terminarPrograma) {
        while( SDL_PollEvent(&event) != 0 ) {
            if(event.type == SDL_QUIT ) {
                terminarPrograma = true;
            }

            // Handle input for mario
            mario.handleEvent( event );
        }

        int inicio = SDL_GetTicks();
        SDL_RenderClear(renderer);
        
        n1.actualizarNivel();
        
        SDL_RenderPresent(renderer);

        int fin = SDL_GetTicks();
        if((fin - inicio) < 1000/FRAMES_POR_SEG)
            SDL_Delay((1000/FRAMES_POR_SEG) - (fin - inicio));
    }

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
} 
