#include "marioView.hpp"

#define LANDING (JUMPING + 1)

MarioView::MarioView(SDL_Renderer *renderer, Mario mario) {

    MarioView::mario = mario;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = MARIO_WIDTH;
    srcRect.h = MARIO_HEIGHT;
                                // TODO: Agregar resizing
    dstRect.x = (int)mario.x;
    dstRect.y = (int)mario.y;
    dstRect.w = MARIO_WIDTH;
    dstRect.h = MARIO_HEIGHT;

    MarioView::renderer = renderer;

    SDL_Surface *surface = IMG_Load("resources/mario.png");
    SDL_SetColorKey(surface, SDL_TRUE, *(Uint32*)(surface->pixels));

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    jumping = 0;
    flip = SDL_FLIP_HORIZONTAL;
    sprite_index = 0;
}

void MarioView::renderCopy() {
    
    switch(mario.action) {
        case STILL:
            updateSpriteStill();
            break;
        case WALKING:
            updateSpriteWalk();
            break;
        case JUMPING:
            updateSpriteJump();
            break;
        case CLIMBING:
            updateSpriteClimb();
            break;
        default:
            break;
    }
    
    dstRect.x = (int)mario.x;
    dstRect.y = (int)mario.y;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0., NULL, flip);
}

void MarioView::updateSpriteStill() {
    srcRect.x = jumping * LANDING * MARIO_SPRITE_SIZE;
    jumping = 0;
}

void MarioView::updateSpriteWalk() {
    if (jumping) {
        srcRect.x = LANDING * MARIO_SPRITE_SIZE;
        jumping = 0;
    } else {
    flip = (SDL_RendererFlip)(dstRect.x < (int)mario.x);
    srcRect.x = ((sprite_index & 2) >> ((sprite_index & 4) >> 2)) * MARIO_SPRITE_SIZE;  // 0, 2, 0, 1...
    sprite_index++;
    }
}

void MarioView::updateSpriteJump() {
    jumping = 1;
    srcRect.x = JUMPING * MARIO_SPRITE_SIZE;
}

void MarioView::updateSpriteClimb() {
    //TODO
}

void MarioView::free() {
    SDL_DestroyTexture(texture);
}
