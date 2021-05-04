#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MARIO_WIDTH 12
#define MARIO_HEIGHT 16
#define MARIO_REST_X 245
#define MARIO_REST_Y 20

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

    SDL_Surface *surface = IMG_Load("resources/sprites_dk2.png");
    Uint32 pixel = *(Uint32*)(surface->pixels);
    SDL_SetColorKey(surface, SDL_TRUE, pixel);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect srcrect;
    srcrect.x = MARIO_REST_X;
    srcrect.y = MARIO_REST_Y;
    srcrect.w = MARIO_WIDTH;
    srcrect.h = MARIO_HEIGHT;

    SDL_Rect dstrect;
    dstrect.w = MARIO_WIDTH * 10;
    dstrect.h = MARIO_HEIGHT * 10;
    dstrect.x = (WINDOW_WIDTH - dstrect.w) >> 1;
    dstrect.y = (WINDOW_HEIGHT - dstrect.h) >> 1;

    SDL_RenderClear(renderer);

    SDL_RendererFlip flip_horiz = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, 0., NULL, flip_horiz);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
} 
