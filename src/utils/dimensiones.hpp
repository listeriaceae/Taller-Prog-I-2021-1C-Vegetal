#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "fixed_point.hpp"

struct dimensions
{
  fixed32_t x1, y1, x2, y2;
};

constexpr bool
intersect(const dimensions &r1, const dimensions &r2) noexcept
{
  return r1.x1 < r2.x2 && r2.x1 < r1.x2 && r1.y1 < r2.y2 && r2.y1 < r1.y2;
}

#endif// DIMENSIONS_H
