#ifndef PLATFORM_H
#define PLATFORM_H

#include <random>
#include "../../utils/punto.hpp"

class Platform
{
public:
  constexpr Platform(fixed32_t x1, fixed32_t y1, fixed32_t x2, fixed32_t y2) noexcept
    : start{ x1, y1 }, end{ x2, y2 }
  {
  }
  inline punto32_t getRandomPoint() const
  {
    std::mt19937 mt{ std::random_device{}() };
    const float t = std::uniform_real_distribution<float>{}(mt);
    return { start.x + static_cast<fixed32_t>(t * (end.x - start.x)),
      start.y + static_cast<fixed32_t>(t * (end.y - start.y)) };
  }
  virtual punto32_t getLimits() const { return getCurrentLimits(); }
  constexpr punto32_t getCurrentLimits() const { return { start.x, end.x }; }
  constexpr fixed32_t getY(fixed32_t x) const
  {
    return start.y + from_fixed32<float>(x - start.x) / from_fixed32<float>(end.x - start.x) * (end.y - start.y);
  }
  constexpr fixed32_t getSpeed() const { return speed; }
  virtual ~Platform() = default;

  punto32_t start, end;
  fixed32_t speed{};
};

#endif
