#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <cstdint>
#include <type_traits>

template<typename T>
concept integral = std::is_integral_v<T>;

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<integral Res, arithmetic In, std::intmax_t Shift>
constexpr Res to_fixed(In src) noexcept
{
  if constexpr (Shift < 0)
    return static_cast<Res>(src / (1 << (-Shift)));
  else
    return static_cast<Res>(src * (1 << Shift));
};

template<integral Res, arithmetic Out, std::intmax_t Shift>
constexpr Out from_fixed(Res src) noexcept
{
  if constexpr (Shift < 0)
    return static_cast<Out>(src * static_cast<Out>(1 << (-Shift)));
  else
    return static_cast<Out>(src / static_cast<Out>(1 << Shift));
};

using fixed16_t = std::int16_t;
using fixed32_t = std::int32_t;

template<arithmetic In> constexpr fixed32_t to_fixed32(In src) noexcept
{
  return to_fixed<fixed32_t, In, 6>(src);
}

template<arithmetic In> constexpr fixed16_t to_fixed16(In src) noexcept
{
  return to_fixed<fixed16_t, In, 6>(src);
}

template<arithmetic Out> constexpr Out from_fixed32(fixed32_t src) noexcept
{
  return from_fixed<fixed32_t, Out, 6>(src);
}

template<arithmetic Out> constexpr Out from_fixed16(fixed16_t src) noexcept
{
  return from_fixed<fixed16_t, Out, 6>(src);
}

#endif// FIXED_POINT_H
