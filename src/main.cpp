#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "model/mario.h"
#include "view/marioView.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Window Title",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

    Mario mario = Mario();
    MarioView marioView = MarioView(renderer, mario);

    int close = 0;
    SDL_Event event;

    while (!close) {
        while (SDL_PollEvent(&event)) close = (event.type == SDL_QUIT);

        SDL_RenderClear(renderer);
        marioView.renderCopy();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }

    marioView.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
} 
