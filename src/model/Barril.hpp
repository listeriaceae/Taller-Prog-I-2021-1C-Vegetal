#ifndef BARRIL_H
#define BARRIL_H

#include "Enemy.hpp"
#include "../utils/Constants.hpp"
#include "../utils/dimensiones.hpp"

#define BARRIL_POINTS 5

class Barril : public Enemy
{
public:
  Barril()
    : Enemy{ { to_fixed32(N2_POS_X_BARRIL), to_fixed32(N2_POS_Y_BARRIL) }, BARRIL_POINTS }
  {
  }
  void mover();
  [[nodiscard]] constexpr bool out_of_bounds() const
  {
    return pos.x > to_fixed32(ANCHO_NIVEL);
  }
  dimensions get_dimensions() const
  {
    return { pos.x, pos.y, pos.x + width, pos.y + height };
  }

private:
  static constexpr auto width = to_fixed32(ANCHO_BARRIL);
  static constexpr auto height = to_fixed32(ALTO_BARRIL);
  punto32_t vel{ to_fixed32(1), 0 };
  std::size_t direcciones_index{};
};

#endif// BARRIL_H
