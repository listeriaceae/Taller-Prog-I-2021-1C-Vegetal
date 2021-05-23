#include <string>
#include "FactoryEnemigos.h"
#include "EnemigoFuego.h"


const std::string FUEGO = "Fuego";

Entidad* FactoryEnemigos::crearEnemigo(std::string tipoEnemigo, int posX, int posY) {
    if(tipoEnemigo.compare(FUEGO) == 0) {
        int numRandom = (rand() % 2);
        int velX;
        if(numRandom == 0)
            velX = -1;
        else
            velX = 1;
        return new EnemigoFuego(posX, posY, velX, 32, 32);
    }
    else
        return NULL;
}