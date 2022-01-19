#ifndef ENEMIGO_FUEGO_H
#define ENEMIGO_FUEGO_H

#include "Enemy.hpp"
#include "../utils/Constants.hpp"
#include "../utils/dimensiones.hpp"


class EnemigoFuego : public Enemy
{
public:
  EnemigoFuego(punto32_t pos, int direccion, fixed32_t min, fixed32_t max);
  void mover();
  dimensions get_dimensions() const
  {
    return { pos.x + x_diff, pos.y + y_diff, pos.x + (width - x_diff), pos.y + height };
  }

private:
  static constexpr auto x_diff = to_fixed32(2);
  static constexpr auto y_diff = to_fixed32(8);
  static constexpr auto width = to_fixed32(ANCHO_ENEMIGO_FUEGO);
  static constexpr auto height = to_fixed32(ALTO_ENEMIGO_FUEGO);
  fixed32_t vel, min, max;
};

#endif// ENEMIGO_FUEGO_H
