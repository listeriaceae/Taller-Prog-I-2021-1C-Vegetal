#ifndef BARRIL_H
#define BARRIL_H

#include "../utils/Constants.hpp"
#include "../utils/dimensiones.hpp"
#include "../utils/punto.hpp"

class Barril
{
public:
  void mover();
  [[nodiscard]] constexpr bool out_of_bounds() const
  {
    return pos.x > to_fixed32(ANCHO_NIVEL);
  }
  dimensions get_dimensions() const
  {
    static constexpr auto width = to_fixed32(ANCHO_BARRIL);
    static constexpr auto height = to_fixed32(ALTO_BARRIL);

    return { pos.x, pos.y, pos.x + width, pos.y + height };
  }

  punto32_t pos{ to_fixed32(N2_POS_X_BARRIL), to_fixed32(N2_POS_Y_BARRIL) };
  std::uint32_t points{ 5 };
  bool isEnabled = true;

private:
  punto32_t vel{ to_fixed32(1), 0 };
  std::size_t direcciones_index{};
};

#endif// BARRIL_H
