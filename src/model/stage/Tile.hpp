#ifndef TILE_H
#define TILE_H

#include <unordered_set>
#include <vector>
#include <optional>
#include "Platform.hpp"
#include "MovingPlatform.hpp"
#include "Ladder.hpp"

/* Representa una celda de dimension ANCHO_TILE y ALTO_TILE
 * que contiene los elementos con los que Mario puede interactuar
 */
class Tile
{
public:
  inline void addPlatform(const Platform *platform) { platforms.push_back(platform); }
  inline void addPlatform(const MovingPlatform *platform) { mplatforms.push_back(platform); }
  inline void getPlatforms(std::unordered_set<const Platform *> &platforms_,
                           std::unordered_set<const MovingPlatform *> &mplatforms_) const
  {
    platforms_.insert(platforms.cbegin(), platforms.cend());
    mplatforms_.insert(mplatforms.cbegin(), mplatforms.cend());
  }
  inline void setLadderBottom(Ladder ladder) { ladderBottom.emplace(std::move(ladder)); }
  inline void setLadderTop(Ladder ladder) { ladderTop.emplace(std::move(ladder)); }

  std::optional<Ladder> ladderBottom{ std::nullopt };
  std::optional<Ladder> ladderTop{ std::nullopt };

private:
  std::vector<const Platform *> platforms;
  std::vector<const MovingPlatform *> mplatforms;
};

#endif// TILE_H
