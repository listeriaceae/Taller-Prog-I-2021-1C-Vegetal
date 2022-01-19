
#include "MovingPlatform.hpp"

static constexpr auto per_cable = 3;
static constexpr auto level0_y = to_fixed32(124);
static constexpr auto x_gap = to_fixed32(58);
static constexpr auto y_gap = to_fixed32(40);
static constexpr auto platform_speed = to_fixed32(0.25);

MovingPlatform::MovingPlatform(int platform, int level)
  : Platform{ 0, 0, 0, 0 }, direction{ ((level + 1) & 2) - 1 }
{
  speed = direction * platform_speed;
  const fixed32_t limit =
    ((right_limit + left_limit) / 2) + direction * ((right_limit - left_limit) / 2);

  start.x = limit - direction * platform * x_gap;
  start.y = level0_y + (level / 2) * y_gap + (level % 2) * to_fixed32(ALTO_PLATAFORMA);
  end.x = start.x + to_fixed32(ANCHO_PLATAFORMA);
  end.y = start.y;
}

void MovingPlatform::move()
{
  start.x += speed;
  if (start.x < left_limit || right_limit < start.x)
    start.x -= this->direction * (per_cable * x_gap);
  end.x = start.x + to_fixed32(ANCHO_PLATAFORMA);
}
