#include <string>
#include "FactoryEnemigos.h"
#include "EnemigoFuego.h"


const std::string FUEGO = "Fuego";
const int ALTO_FUEGO = 32;
const int ANCHO_FUEGO = 32;

Entidad* FactoryEnemigos::crearEnemigo(std::string tipoEnemigo, int posX, int posY) {
    if(tipoEnemigo.compare(FUEGO) == 0) {
        int numRandom = (rand() % 2);
        int velX;
        if(numRandom == 0)
            velX = -1;
        else
            velX = 1;
        return new EnemigoFuego(posX, posY, velX, ANCHO_FUEGO, ALTO_FUEGO);
    }
    else
        return NULL;
}