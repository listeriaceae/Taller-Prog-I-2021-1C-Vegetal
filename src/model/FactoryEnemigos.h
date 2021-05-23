#pragma once

#include <string>
#include "Entidad.h"

class FactoryEnemigos {
    public:

    Entidad* crearEnemigo(std::string tipoEnemigo, int posX, int posY);

    private:

};