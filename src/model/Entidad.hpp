#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "../utils/punto.hpp"

class Entidad
{
public:
  constexpr Entidad(punto32_t pos_) noexcept : pos{ pos_ } {};
  virtual ~Entidad() = default;

  punto32_t pos;
  bool isEnabled = true;
};

template<typename T>
concept has_pos = requires(T t) { t.pos; };

template<typename E>
requires has_pos<E> constexpr punto16_t
  get_pos(const E &e) noexcept
{
  return { static_cast<fixed16_t>(e.pos.x), static_cast<fixed16_t>(e.pos.y) };
}

#endif// ENTIDAD_H
