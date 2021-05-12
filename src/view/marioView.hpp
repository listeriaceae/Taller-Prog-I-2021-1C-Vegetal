#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../model/mario.hpp"

#define MARIO_WIDTH 16
#define MARIO_HEIGHT 16
#define MARIO_SPRITE_SIZE 24

class MarioView {
    private:
        Mario mario;
        int jumping;
        int sprite_index;
        SDL_RendererFlip flip;
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        SDL_Renderer *renderer;
        SDL_Texture *texture;

        void updateSpriteStill();
        void updateSpriteWalk();
        void updateSpriteJump();
        void updateSpriteClimb();

    public:
        MarioView(SDL_Renderer*, Mario);
        void renderCopy();
        void free();
};