// Build command: g++ main.cpp -o bin/main -Wall -Wextra -std=c++17 -ggdb -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -Iinclude -Llib

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Nivel1.h"
#include "Barril.h"
#include "Fuego.h"
#include "PlataformaMovil.h"
#include "EnemigoFuego.h"
#include "Peach.h"

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 600;
const int FRAMES_POR_SEG = 60;
int main(void)
{
    // TODO: Handle errors...

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Window Title1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Init(SDL_INIT_VIDEO);
    bool terminarPrograma = false;

    SDL_Event event;
    
    Nivel1 n1(renderer);

    PlataformaMovil m1(200, 288, -4, 60, 19);
    PlataformaMovil m2(400, 307, 4, 60, 19);
    PlataformaMovil m3(250, 382, -4, 60, 19);
    PlataformaMovil m4(300, 401, 4, 60, 19);

    Fuego f1(172, 544, 56, 56);
    Fuego f2(314, 544, 56, 56);
    Fuego f3(458, 544, 56, 56);
    Fuego f4(600, 544, 56, 56);

    EnemigoFuego e1(400, 437, 1, 32, 32);
    EnemigoFuego e2(617, 171, -1, 32, 32);
    //Barril b1(300, 0, 0, 10);
    //Barril b2(200, 0, 0, 7);

    Peach p1(314, 76, 40, 55);

    while(!terminarPrograma) {
        while( SDL_PollEvent(&event) != 0 ) {
            if(event.type == SDL_QUIT ) {
                terminarPrograma = true;
            }
        }
        int inicio = SDL_GetTicks();
        SDL_RenderClear(renderer);
        
        n1.actualizarVista(); 
        /*
        b1.mover();
        b2.mover();

        b1.mostrar(renderer);
        b2.mostrar(renderer);
        */
        e1.mover();
        e2.mover();

        e1.mostrar(renderer);
        e2.mostrar(renderer);
        
        m1.mover();
        m2.mover();
        m3.mover();
        m4.mover();

        m1.mostrar(renderer);
        m2.mostrar(renderer);
        m3.mostrar(renderer);
        m4.mostrar(renderer);

        f1.mostrar(renderer);
        f2.mostrar(renderer);
        f3.mostrar(renderer);
        f4.mostrar(renderer);

        p1.mostrar(renderer);
        SDL_RenderPresent(renderer);

        int fin = SDL_GetTicks();
        if((fin - inicio) < 1000/FRAMES_POR_SEG)
            SDL_Delay((1000 - (fin - inicio))/FRAMES_POR_SEG);
    }

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
} 
