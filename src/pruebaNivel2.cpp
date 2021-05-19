#include <SDL2/SDL.h>
#include <string>
#include "level2.h"

using namespace std;

int main(void)
{
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Donkey Kong II - Level 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    Level2 level(renderer); 

    bool endProgram = false;

    SDL_Event event;

    while(!endProgram) {
        while( SDL_PollEvent(&event) != 0 ) {
            if(event.type == SDL_QUIT ) {
                endProgram = true;
            }
        }
        level.updateView();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
} 