#ifndef PUNTO_H
#define PUNTO_H
#include "fixed_point.hpp"

template<arithmetic T>
struct punto
{
  T x{};
  T y{};
  [[nodiscard]] constexpr bool
  operator==(const punto &rhs) const noexcept
  {
    return x == rhs.x && y == rhs.y;
  };
  [[nodiscard]] constexpr punto
  operator+(const punto &rhs) const noexcept
  {
    return { static_cast<T>(x + rhs.x), static_cast<T>(y + rhs.y) };
  }
  [[nodiscard]] constexpr punto
  operator-(const punto &rhs) const noexcept
  {
    return { static_cast<T>(x - rhs.x), static_cast<T>(y - rhs.y) };
  }
};

using punto16_t = punto<fixed16_t>;
using punto32_t = punto<fixed32_t>;

#endif// PUNTO_H
