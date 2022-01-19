#include <unordered_set>
#include "Stage.hpp"

static constexpr auto stage_width = to_fixed32(ANCHO_NIVEL / ANCHO_TILE);
static constexpr auto stage_height = to_fixed32(ALTO_NIVEL / ALTO_TILE);
static constexpr auto grid_columns = (ANCHO_NIVEL / ANCHO_TILE) + 1;
static constexpr auto slope = to_fixed32(0.03125);
static constexpr auto hitbox_width = to_fixed32(8);
static constexpr auto mario_width = to_fixed32(ANCHO_MARIO);
static constexpr auto mario_height = to_fixed32(ALTO_MARIO);

void Stage::addLadder(Ladder ladder)
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

void Stage::addPlatform(const Platform *platform)
{
  auto [x, max] = platform->getLimits();
  std::size_t i;
  do {
    i = (platform->getY(x) / stage_height) * grid_columns + x / stage_width;
    grid[i].addPlatform(platform);
    x += ANCHO_TILE;
  } while (x < max);
  Tile &tile =
    grid[(platform->getY(max) / stage_height) * grid_columns + max / stage_width];
  if (&grid[i] != &tile) {
    tile.addPlatform(platform);
  }
}

bool Stage::collide(fixed32_t &x, fixed32_t &y, fixed32_t &dx, fixed32_t &dy) const
{
  std::unordered_set<const Platform *> platforms;
  platforms.reserve(8);
  {
    const std::size_t i = (y / stage_height) * grid_columns + x / stage_width;
    grid[i].getPlatforms(platforms);
    grid[i + 1].getPlatforms(platforms);
    grid[i + grid_columns].getPlatforms(platforms);
    grid[i + (grid_columns + 1)].getPlatforms(platforms);
  }
  bool is_standing = false;
  for (auto it = platforms.begin(); it != platforms.end(); ++it) {
    const auto [min, max] = (*it)->getCurrentLimits();
    const auto distanceLeft = x - min + (mario_width / 2 + hitbox_width / 2);
    const auto distanceRight = max - x - (mario_width / 2 - hitbox_width / 2);
    if (0 < distanceLeft && 0 < distanceRight) {
      const auto distanceY = y + mario_height - (*it)->getY(x);
      if (0 <= distanceY) {
        const bool hit_wall = distanceY <= to_fixed32(3 * ALTO_MARIO / 4) && (distanceRight <= to_fixed32(1) || distanceLeft <= to_fixed32(1));
        x -= distanceLeft * (distanceLeft <= to_fixed32(1) && hit_wall);
        x += distanceRight * (distanceRight <= to_fixed32(1) && hit_wall);
        dx &= hit_wall - 1;

        const bool hit_floor =
          !hit_wall && (distanceY <= slope - dy || (distanceY <= to_fixed32(1) && dy <= 0));
        y -= distanceY & (-hit_floor);
        dy &= hit_floor - 1;
        x += (*it)->getSpeed() & (-hit_floor);
        is_standing |= hit_floor;
      }
    }
  }
  return is_standing;
}
