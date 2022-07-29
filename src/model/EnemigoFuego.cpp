#include "EnemigoFuego.hpp"

#define ENEMIGO_FUEGO_VEL 0.5f

EnemigoFuego::EnemigoFuego(punto32_t pos_,
                           int direccion,
                           fixed32_t min_,
                           fixed32_t max_)
  : pos{ pos_ }, vel{ to_fixed32(direccion * ENEMIGO_FUEGO_VEL) },
    min{ min_ - to_fixed32(ANCHO_ENEMIGO_FUEGO) / 2 }, max{
      max_ - to_fixed32(ANCHO_ENEMIGO_FUEGO) / 2
    }
{}

void
EnemigoFuego::mover()
{
  vel = pos.x < min || pos.x > max ? -vel : vel;
  pos.x += vel;
}
