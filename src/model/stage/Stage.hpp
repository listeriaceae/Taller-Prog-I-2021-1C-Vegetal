#ifndef STAGE_H
#define STAGE_H

#include <array>
#include "Tile.hpp"
#include "Ladder.hpp"
#include "Platform.hpp"
#include "MovingPlatform.hpp"
#include "../../utils/Constants.hpp"


/* Representa todos los elementos del nivel con los que Mario puede interactuar
 * Contiene un arreglo de Tiles
 */
class Stage
{
public:
  void addLadder(Ladder ladder);
  std::optional<Ladder> getLadder(fixed32_t x, fixed32_t y, int direction) const;
  void addPlatform(const Platform *platform);
  void addPlatform(const MovingPlatform *mplatform);
  bool collide(fixed32_t &x, fixed32_t &y, fixed32_t &dx, fixed32_t &dy) const;

private:
  std::array<Tile, (ANCHO_NIVEL / ANCHO_TILE + 1) * (ALTO_NIVEL / ALTO_TILE + 1)> grid{};
};

#endif// STAGE_H
