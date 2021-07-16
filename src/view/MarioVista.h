#pragma once

#include <SDL2/SDL.h>
#include "../utils/marioStructs.h"

class MarioVista
{
public:
    MarioVista(SDL_Renderer *renderer);
    MarioVista(const MarioVista &other);
    void mostrar(const estadoMario_t &estado);
    void setColor(size_t color);
    ~MarioVista();

private:
    static SDL_Renderer *renderer;
    static SDL_Texture *texture;
    static SDL_Texture *hammerTexture;
    static size_t totalJugadores;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    SDL_Rect hammerSrc;
    SDL_Rect hammerDst;
    SDL_RendererFlip flip{SDL_FLIP_HORIZONTAL};
    int tiempo{0};

    void updateReposo(char estado, bool hasHammer);
    void updateCorriendo(int nextX, bool hasHammer);
    void updateSaltando(int nextX);
    void updateTrepando(int nextY);
    void updateMuriendo(char estado);
    void loadHammerTexture();
    int frameActual = 0;
    void drawHammer(char estado);
};