#pragma once
#include <string.h>
#include <SDL2/SDL.h>

using namespace std;

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 600;

class Barril {
public:

    static const int alto = 40;
    static const int ancho = 40;

    Barril(int posX, int posY, int velX, int velY, string rutaImagen);

    ~Barril();

    void mover();

    void inicializarImagen(SDL_Renderer* renderer);

    void mostrar(SDL_Renderer* renderer);

    int getX();

    int getY();
private:
    string rutaImagen;
    SDL_Surface* surface = NULL;
    SDL_Texture* imagen = NULL;
    Uint32 tickUltimoMovimiento = 0;
    int posX = 0;
    int posY = 0;

    int velX = 0;
    int velY = 0;
};