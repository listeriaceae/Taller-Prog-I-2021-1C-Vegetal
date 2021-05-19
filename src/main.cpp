#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include "model/Entidad.h"
#include "model/Nivel1.h"
#include "model/Nivel2.h"
#include "model/Barril.h"
#include "model/Fuego.h"
#include "model/PlataformaMovil.h"
#include "model/EnemigoFuego.h"
#include "model/Peach.h"
#include "model/Mario.hpp"
#include <string>
#include "model/DonkeyKong.h"
#include "configuration.hpp"
#include "logger.h"
#include "window.hpp"
#include "utils/ Constants.hpp"

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

    Mario mario( Constants::N1_MARIO_POS_X, 
                 Constants::N1_MARIO_POS_Y,
                 Constants::MARIO_ANCHO,
                 Constants::MARIO_ALTO);
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
            
            // Cambio de nivel
            if( event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_TAB) {
                logger::Logger::getInstance().logInformation("End of Level 1");
                goto nivel2;
            }

            // Handle input for Mario
            mario.handleEvent( event );
        }

        int inicio = SDL_GetTicks();
        SDL_RenderClear(renderer);
        
        n1.actualizarNivel();
        
        SDL_RenderPresent(renderer);


        int fin = SDL_GetTicks();
        if((fin - inicio) < 1000/FRAMES_POR_SEG)
        {
            SDL_Delay((1000/FRAMES_POR_SEG) - (fin - inicio));
        }
    }

    nivel2:
        SDL_RenderClear(renderer);
        Nivel2 n2(renderer); 
        logger::Logger::getInstance().logInformation("Level 2 starts");
        
        mario = Mario( Constants::N2_MARIO_POS_X, 
                       Constants::N2_MARIO_POS_Y,
                       Constants::MARIO_ANCHO,
                       Constants::MARIO_ALTO);
        
        n2.addElement(&mario);

        while(!terminarPrograma) {
        while( SDL_PollEvent(&event) != 0 ) {
            if(event.type == SDL_QUIT ) {
                terminarPrograma = true;
            }

            if( event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_TAB) {
                logger::Logger::getInstance().logInformation("End of Level 2");
                goto fin;
            }

            // Handle input for mario
            mario.handleEvent( event );
        }

        int inicio = SDL_GetTicks();

        SDL_RenderClear(renderer);
        n2.updateView();
        SDL_RenderPresent(renderer);

        int fin = SDL_GetTicks();
        if((fin - inicio) < 1000/FRAMES_POR_SEG)
        SDL_Delay((1000/FRAMES_POR_SEG) - (fin - inicio));
    };

    fin:
        logger::Logger::getInstance().logInformation("Game over");

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
} 
