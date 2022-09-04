#include <unordered_set>
#include <utility>
#include "Stage.hpp"

static constexpr auto stage_width = to_fixed32(ANCHO_NIVEL / ANCHO_TILE);
static constexpr auto stage_height = to_fixed32(ALTO_NIVEL / ALTO_TILE);
static constexpr auto grid_columns = (ANCHO_NIVEL / ANCHO_TILE) + 1;
static constexpr auto stepsize = to_fixed32(1);
static constexpr auto hitbox_width = to_fixed32(8);
static constexpr auto mario_width = to_fixed32(ANCHO_MARIO);
static constexpr auto mario_height = to_fixed32(ALTO_MARIO);

void
Stage::addLadder(Ladder ladder)
{
  const std::size_t x = (ladder.x + mario_width / 2) / stage_width;
  {
    const std::size_t y = ladder.bottom / stage_height;
    grid[y * grid_columns + x].setLadderBottom(ladder);
  }
  const std::size_t y = ladder.top / stage_height;
  grid[y * grid_columns + x].setLadderTop(ladder);
}

std::optional<Ladder>
Stage::getLadder(fixed32_t x, fixed32_t y, int direction) const
{
  const std::size_t i =
    (y / stage_height) * grid_columns + (x + mario_width / 2) / stage_width;
  if (0 < direction)
    return grid[i].ladderBottom;
  if (direction < 0)
    return grid[i].ladderTop;
  return std::nullopt;
}

void
Stage::addPlatform(const Platform *platform)
{
  auto [x, max] = platform->getLimits();
  const auto j = (platform->y / stage_height) * grid_columns;
  std::size_t i;
  do {
    i = j + x / stage_width;
    grid[i].addPlatform(platform);
    x += ANCHO_TILE;
  } while (x < max);

  if (std::cmp_not_equal(i, j + max / stage_width))
    grid[j + max / stage_width].addPlatform(platform);
}


void
Stage::addPlatform(const MovingPlatform *mplatform)
{
  auto [x, max] = mplatform->getRange();
  const auto j = (mplatform->pos.y / stage_height) * grid_columns;
  std::size_t i;
  do {
    i = j + x / stage_width;
    grid[i].addPlatform(mplatform);
    x += ANCHO_TILE;
  } while (x < max);

  if (std::cmp_not_equal(i, j + max / stage_width))
    grid[j + max / stage_width].addPlatform(mplatform);
}

bool
Stage::collide(fixed32_t &x, fixed32_t &y, fixed32_t &dx, fixed32_t &dy) const
{
  std::unordered_set<const Platform *> platforms{ 3 };
  std::unordered_set<const MovingPlatform *> mplatforms{ 6 };
  {
    const std::size_t i = (y / stage_height) * grid_columns + x / stage_width;
    grid[i].getPlatforms(platforms, mplatforms);
    grid[i + 1].getPlatforms(platforms, mplatforms);
    grid[i + grid_columns].getPlatforms(platforms, mplatforms);
    grid[i + (grid_columns + 1)].getPlatforms(platforms, mplatforms);
  }
  bool is_standing = false;
  for (auto it = platforms.begin(); it != platforms.end(); ++it) {
    const auto [min, max] = (*it)->getLimits();
    const auto distanceLeft = x - min + (mario_width / 2 + hitbox_width / 2);
    const auto distanceRight = max - x - (mario_width / 2 - hitbox_width / 2);
    if (0 < distanceLeft && 0 < distanceRight) {
      const auto distanceY = y + mario_height - (*it)->y;
      if (0 <= distanceY) {
        if (distanceY <= stepsize - dy) {
          y -= distanceY;
          dy = 0;
          is_standing = true;
        } else if (to_fixed32(2) < distanceY
                   && distanceY <= to_fixed32(3 * ALTO_MARIO / 4)) {
          if (distanceLeft <= to_fixed32(1))
            x -= distanceLeft;
          else if (distanceRight <= to_fixed32(1))
            x += distanceRight;
          dx = 0;
        }
      }
    }
  }
  for (auto it = mplatforms.begin(); it != mplatforms.end(); ++it) {
    const auto [min, max] = (*it)->getLimits();
    const auto distanceLeft = x - min + (mario_width / 2 + hitbox_width / 2);
    const auto distanceRight = max - x - (mario_width / 2 - hitbox_width / 2);
    if (0 < distanceLeft && 0 < distanceRight) {
      const auto distanceY = y + mario_height - (*it)->pos.y;
      if (0 <= distanceY) {
        if (distanceY <= to_fixed32(3 * ALTO_MARIO / 4)
            && std::min(distanceLeft, distanceRight) <= to_fixed32(1)) {
          if (distanceLeft <= to_fixed32(1))
            x -= distanceLeft;
          else if (distanceRight <= to_fixed32(1))
            x += distanceRight;
          dx = 0;
        } else if (distanceY <= -dy) {
          x += (*it)->speed;
          y -= distanceY;
          dy = 0;
          is_standing = true;
        }
      }
    }
  }
  return is_standing;
}
