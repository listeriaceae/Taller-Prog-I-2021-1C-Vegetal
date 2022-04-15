#ifndef PLATFORM_H
#define PLATFORM_H

#include <random>
#include "../../utils/punto.hpp"

class Platform
{
public:
  constexpr Platform(fixed32_t x1, fixed32_t x2, fixed32_t y_)
    : start{ x1 }, width{ x2 - x1 }, y{ y_ }
  {
  }
  [[nodiscard]] inline punto32_t getRandomPoint() const
  {
    std::mt19937 mt{ std::random_device{}() };
    const auto x = std::uniform_int_distribution<fixed32_t>{start, start + width}(mt);
    return { x, y };
  }
  [[nodiscard]] constexpr punto32_t getLimits() const
  {
    return { start, start + width };
  }

  fixed32_t start, width, y;
};

#endif
