// Build command: g++ main.cpp -o bin/main -Wall -Wextra -std=c++17 -ggdb -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -Iinclude -Llib

#include <iostream>
#include <SDL2/SDL.h>
#include "Barril.h"

int main(void)
{
    // TODO: Handle errors...

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Window Title1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    bool terminarPrograma = false;

    SDL_Event event;
    Barril b1(300, 0, 0, 10, "Barril.bmp");
    Barril b2(200, 0, 0, 7, "Barril.bmp");
    b1.inicializarImagen(renderer);
    b2.inicializarImagen(renderer);

    while(!terminarPrograma) {
        while( SDL_PollEvent(&event) != 0 ) {
            if(event.type == SDL_QUIT ) {
                terminarPrograma = true;
            }
        }
        b1.mover();
        b2.mover();

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        b1.mostrar(renderer);
        b2.mostrar(renderer);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
} 
