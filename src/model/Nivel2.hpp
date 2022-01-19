#ifndef NIVEL_2_H
#define NIVEL_2_H

#include "Nivel.hpp"
#include "Barril.hpp"

class Nivel2 : public Nivel
{
public:
  Nivel2(std::vector<Mario> *players);
  void update() override;
  LevelState getEstado() const override;

private:
  std::vector<Barril> barriles;
  size_t tick = 0;

  void initPlatforms();
  void initLadders();
  void initHammers();

  void checkCollisions();
  void erase_out_of_bounds();

private:
  std::array<Platform, 9> platforms{
    Platform{ to_fixed32(0.f), to_fixed32(248.f), to_fixed32(120.f), to_fixed32(248.f) },
    { to_fixed32(112.f), to_fixed32(248.f), to_fixed32(224.f), to_fixed32(241.f) },
    { to_fixed32(0.f), to_fixed32(208.f), to_fixed32(208.f), to_fixed32(221.f) },
    { to_fixed32(16.f), to_fixed32(188.f), to_fixed32(224.f), to_fixed32(175.f) },
    { to_fixed32(0.f), to_fixed32(142.f), to_fixed32(208.f), to_fixed32(155.f) },
    { to_fixed32(16.f), to_fixed32(122.f), to_fixed32(224.f), to_fixed32(109.f) },
    { to_fixed32(136.f), to_fixed32(84.5f), to_fixed32(208.f), to_fixed32(89.f) },
    { to_fixed32(0.f), to_fixed32(84.f), to_fixed32(130.f), to_fixed32(84.f) },
    { to_fixed32(88.f), to_fixed32(56.f), to_fixed32(135.f), to_fixed32(56.f) }
  };
};

#endif// NIVEL_2_H
