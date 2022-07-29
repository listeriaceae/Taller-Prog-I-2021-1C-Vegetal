#ifndef M_PLATFORM_H
#define M_PLATFORM_H

#include "../../utils/Constants.hpp"
#include "../../utils/punto.hpp"

class MovingPlatform
{
public:
  MovingPlatform(int platform, int level);
  void move();
  [[nodiscard]] constexpr punto32_t
  getLimits() const
  {
    return { pos.x, pos.x + width };
  }
  [[nodiscard]] static constexpr punto32_t
  getRange()
  {
    return { left_limit, right_limit + width };
  }

  punto32_t pos{};
  fixed32_t speed{};
  static constexpr auto width = to_fixed32(ANCHO_PLATAFORMA);

private:
  static constexpr auto left_limit = to_fixed32(17);
  static constexpr auto right_limit = to_fixed32(191);
};

[[nodiscard]] constexpr punto16_t
get_start(const MovingPlatform &mp)
{
  return { static_cast<fixed16_t>(mp.pos.x), static_cast<fixed16_t>(mp.pos.y) };
}

#endif// M_PLATFORM_H
