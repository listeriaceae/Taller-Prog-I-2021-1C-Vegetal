#ifndef M_PLATFORM_H
#define M_PLATFORM_H

#include "Platform.hpp"
#include "../../utils/Constants.hpp"
#include "../../utils/fixed_point.hpp"

class MovingPlatform : public Platform
{
public:
  MovingPlatform(int platform, int level);
  void move();
  [[nodiscard]] punto32_t getLimits() const override
  {
    return { left_limit, right_limit + to_fixed32(ANCHO_PLATAFORMA) };
  }

private:
  static constexpr auto left_limit = to_fixed32(17);
  static constexpr auto right_limit = to_fixed32(191);
  int direction;
};

[[nodiscard]] constexpr punto16_t
  get_start(const Platform &mp) noexcept
{
  return { static_cast<fixed16_t>(mp.start.x), static_cast<fixed16_t>(mp.start.y) };
}

#endif// M_PLATFORM_H
