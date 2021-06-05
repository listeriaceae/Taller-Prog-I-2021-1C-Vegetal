#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "model/Nivel1.h"
#include "model/Nivel2.h"
#include "view/Nivel1Vista.h"
#include "view/Nivel2Vista.h"
#include "model/Mario.hpp"
#include "controller/MarioController.h"
#include "configuration.hpp"
#include "logger.h"
#include "utils/window.hpp"
#include "utils/Constants.hpp"

void getNextLevel(Nivel **nivel, NivelVista **vista, Mario* mario, configuration::GameConfiguration *config, Uint8 currentLevel, SDL_Renderer *renderer);

int main(void)
{
    logger::Logger::getInstance().logNewGame();
    
    auto configuration = configuration::GameConfiguration(CONFIG_FILE);
    auto log_level = configuration.getLogLevel();
    logger::Logger::getInstance().setLogLevel(log_level);

    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(NOMBRE_JUEGO.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;

    Mario *mario = new Mario();
    MarioController *marioController = new MarioController(mario);

    Uint8 currentLevel = 1;
    Nivel *nivel = NULL;
    NivelVista *vista = NULL;
    getNextLevel(&nivel, &vista, mario, &configuration, currentLevel, renderer);

    // Game loop design by http://gameprogrammingpatterns.com/game-loop.html#play-catch-up
    Uint32 previous, current, elapsed, lag;
    bool updated, quitRequested = false;
    previous = SDL_GetTicks();
    lag = 0;
    while (!quitRequested) {
        current = SDL_GetTicks();
        elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // Handle quit request
        quitRequested = SDL_QuitRequested();
        // Handle input for Mario
        marioController->update();

        while (SDL_PollEvent(&event)) {
            // Cambio de nivel
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_TAB) {
                char buffer[15];
                sprintf(buffer, "End of Level %d", currentLevel++);
                logger::Logger::getInstance().logInformation(buffer);
                getNextLevel(&nivel, &vista, mario, &configuration, currentLevel, renderer);
            }
        }
        if (nivel == NULL) break;

        // Update Model
        updated = false;
        while (lag >= MS_PER_UPDATE) {
            nivel->update();
            lag -= MS_PER_UPDATE;
            updated = true;
        }

        // Update View and render
        if (updated) {
            SDL_RenderClear(renderer);
            vista->update(nivel->getEstado());
            SDL_RenderPresent(renderer);
        }
    }
    logger::Logger::getInstance().logInformation("Game over");

    delete marioController;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

void getNextLevel(Nivel **nivel, NivelVista **vista, Mario* mario, configuration::GameConfiguration *config, Uint8 currentLevel, SDL_Renderer *renderer) {
    if (currentLevel == 1) {
        logger::Logger::getInstance().logInformation("Level 1 starts");
        mario->setStartPos(N1_MARIO_POS_X, N1_MARIO_POS_Y);

        *nivel = new Nivel1();
        (*nivel)->addPlayer(mario);

        auto enemies = config->getEnemies();
        for (auto enemy: enemies) {
            if (enemy.getType().compare("Fuego") == 0) (*nivel)->addEnemies(enemy.getQuantity());
            logger::Logger::getInstance().logDebug("Enemy type: " + enemy.getType());
            logger::Logger::getInstance().logDebug("Enemy quantity: " + std::to_string(enemy.getQuantity()));
        }

        *vista = new Nivel1Vista(renderer, config->getDefaultConfigFlag());
        (*vista)->addPlayers(1);                                           // Aca iria cantidad de jugadores
        auto stages = config->getStages();
        if (stages.size() > 0) {
            std::string rutaImagen = stages[0].getBackgrounds()[0];
            logger::Logger::getInstance().logDebug("Stage 1 background img: " + rutaImagen);
            (*vista)->setBackground(rutaImagen);
        }
        return;
    }
    if (currentLevel == 2) {
        logger::Logger::getInstance().logInformation("Level 2 starts");
        mario->setStartPos(N2_MARIO_POS_X, N2_MARIO_POS_Y);

        delete *nivel;
        *nivel = new Nivel2();
        (*nivel)->addPlayer(mario);

        delete *vista;
        *vista = new Nivel2Vista(renderer, config->getDefaultConfigFlag());
        (*vista)->addPlayers(1);                                           // Aca iria cantidad de jugadores
        auto stages = config->getStages();
        if (stages.size() > 1) {
            std::string rutaImagen = stages[1].getBackgrounds()[0];
            logger::Logger::getInstance().logDebug("Stage 2 background img: " + rutaImagen);
            (*vista)->setBackground(rutaImagen);
        }
        return;
    } else {
        delete *nivel;
        delete *vista;
        delete mario;
        *nivel = NULL;
    }
}