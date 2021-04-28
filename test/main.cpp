// Build command: g++ main.cpp -o bin/main -Wall -Wextra -std=c++17 -ggdb -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -Iinclude -Llib

#include <SDL2/SDL.h>

int main(void)
{
    // TODO: Handle errors...

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Surface *window_surface = SDL_GetWindowSurface( window ); 

    SDL_FillRect(window_surface, nullptr, SDL_MapRGB(window_surface->format, 0, 0, 0));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
} 
