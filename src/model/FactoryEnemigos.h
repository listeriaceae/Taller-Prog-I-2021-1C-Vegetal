#pragma once

#include <string>
#include "Entidad.h"

class FactoryEnemigos {
    public:

    Entidad* crearEnemigo(std::string tipoEnemigo, float posX, float posY, SDL_Renderer* renderer);

    private:

};