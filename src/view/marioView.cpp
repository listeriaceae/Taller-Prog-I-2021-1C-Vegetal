#include "marioView.h"

MarioView::MarioView(SDL_Renderer *renderer, Mario mario) {

    MarioView::mario = mario;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = MARIO_WIDTH;
    srcRect.h = MARIO_HEIGHT;

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
        case WALK:
            updateSpriteWalk();
            break;
        case JUMP:
            updateSpriteJump();
            break;
        case CLIMB:
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
    sprite_index = jumping;
    srcRect.x = (jumping * JUMP + sprite_index) * MARIO_SPRITE_SIZE;
    jumping = 0;
}

void MarioView::updateSpriteWalk() {
    if (jumping) {
        srcRect.x = (JUMP + 1) * MARIO_SPRITE_SIZE;
        jumping = 0;
    } else {
    flip = (SDL_RendererFlip)(dstRect.x < (int)mario.x);
    srcRect.x = ((sprite_index & 2) >> ((sprite_index & 4) >> 2)) * MARIO_SPRITE_SIZE;
    sprite_index = (sprite_index + 1) % 8;
    }
}

void MarioView::updateSpriteJump() {
    jumping = 1;
    srcRect.x = JUMP * MARIO_SPRITE_SIZE;
}

void MarioView::updateSpriteClimb() {
    //TODO
}

void MarioView::free() {
    SDL_DestroyTexture(texture);
}
