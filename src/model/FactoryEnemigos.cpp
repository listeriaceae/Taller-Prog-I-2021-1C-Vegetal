#include <string>
#include "FactoryEnemigos.h"
#include "EnemigoFuego.h"


const std::string FUEGO = "Fuego";

Entidad* FactoryEnemigos::crearEnemigo(std::string tipoEnemigo, float posX, float posY, SDL_Renderer* renderer) {
    if(tipoEnemigo.compare(FUEGO) == 0) {
        int numRandom = (rand() % 2);
        int velX;
        if(numRandom == 0) velX = -1;
        else velX = 1;
        
        return new EnemigoFuego(posX, posY, velX, renderer);
    }
    else
        return NULL;
}