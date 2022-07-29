#include "MovingPlatform.hpp"

MovingPlatform::MovingPlatform(int platform, int level)
{
  static constexpr auto level0_y = to_fixed32(124);
  static constexpr auto platform_speed = to_fixed32(0.25);
  static constexpr auto x_gap = to_fixed32(58);
  static constexpr auto y_gap = to_fixed32(40);

  const int direction{ ((level + 1) & 2) - 1 };
  const fixed32_t limit = ((right_limit + left_limit) / 2)
                          + direction * ((right_limit - left_limit) / 2);

  speed = direction * platform_speed;
  pos.x = limit - direction * platform * x_gap;
  pos.y =
    level0_y + (level / 2) * y_gap + (level % 2) * to_fixed32(ALTO_PLATAFORMA);
}

void
MovingPlatform::move()
{
  pos.x += speed;
  if (pos.x < left_limit)
    pos.x -= (left_limit - right_limit);
  else if (right_limit < pos.x)
    pos.x -= (right_limit - left_limit);
}
