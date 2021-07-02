#pragma once
#include "NivelVista.h"
#include "BarrilVista.h"

class Nivel2Vista : public NivelVista
{
public:
    Nivel2Vista(SDL_Renderer *renderer, bool defaultConfig, const char* clientUsername);
    void update(estadoJuego_t *estadoJuego);
    ~Nivel2Vista();

private:
    BarrilVista *barrilVista;
    char clientUsername[11];
};