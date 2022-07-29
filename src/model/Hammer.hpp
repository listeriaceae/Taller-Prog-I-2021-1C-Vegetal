#ifndef HAMMER_H
#define HAMMER_H

#include "../utils/fixed_point.hpp"
#include "../utils/punto.hpp"
#include "../utils/dimensiones.hpp"

class Hammer
{
public:
  constexpr Hammer(punto32_t pos_) noexcept : pos{ pos_ } {}
  constexpr dimensions
  get_dimensions() const noexcept
  {
    return { pos.x + x_diff, pos.y + y_diff, pos.x + width, pos.y + height };
  }
  constexpr void
  consume() noexcept
  {
    pos = {};
  }
  punto32_t pos;

private:
  static constexpr auto width = to_fixed32(13);
  static constexpr auto height = to_fixed32(16);
  static constexpr auto x_diff = to_fixed32(4);
  static constexpr auto y_diff = to_fixed32(6);
};

#endif// HAMMER_H
