#pragma once
#include "NivelVista.h"
#include "PlataformaMovilVista.h"
#include "EnemigoFuegoVista.h"

class Nivel1Vista : public NivelVista
{
public:
    Nivel1Vista(SDL_Renderer *renderer, bool defaultConfig, const char* clientUsername);
    void update(estadoJuego_t *estadoJuego);
    ~Nivel1Vista();

private:
    PlataformaMovilVista *plataformaVista;
    EnemigoFuegoVista *enemigoVista;
    char clientUsername[11];
};