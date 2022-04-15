#ifndef NIVEL_1_H
#define NIVEL_1_H

#include "stage/MovingPlatform.hpp"
#include "EnemigoFuego.hpp"
#include "Nivel.hpp"

class Nivel1 : public Nivel
{
public:
  Nivel1(std::vector<Mario> *players);
  void update() override;
  LevelState getEstado() const override;

private:
  std::array<MovingPlatform, 12> movingPlatforms{ { { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { 0, 1 },
    { 1, 1 },
    { 2, 1 },
    { 0, 2 },
    { 1, 2 },
    { 2, 2 },
    { 0, 3 },
    { 1, 3 },
    { 2, 3 } } };
  static constexpr std::array<Platform, 18> platforms{
    Platform
    { to_fixed32(64), to_fixed32(88), to_fixed32(248) },
    { to_fixed32(104), to_fixed32(128), to_fixed32(248) },
    { to_fixed32(144), to_fixed32(168), to_fixed32(248) },
    { to_fixed32(184), to_fixed32(224), to_fixed32(248) },
    { to_fixed32(0), to_fixed32(48), to_fixed32(200) },
    { to_fixed32(64), to_fixed32(88), to_fixed32(200) },
    { to_fixed32(104), to_fixed32(128), to_fixed32(200) },
    { to_fixed32(144), to_fixed32(168), to_fixed32(200) },
    { to_fixed32(184), to_fixed32(224), to_fixed32(200) },
    { to_fixed32(160), to_fixed32(192), to_fixed32(87) },
    { to_fixed32(24), to_fixed32(144), to_fixed32(84) },
    { to_fixed32(208), to_fixed32(224), to_fixed32(160) },
    { to_fixed32(0), to_fixed32(16), to_fixed32(160) },
    { to_fixed32(0), to_fixed32(16), to_fixed32(120) },
    { to_fixed32(208), to_fixed32(224), to_fixed32(120) },
    { to_fixed32(208), to_fixed32(224), to_fixed32(88) },
    { to_fixed32(0), to_fixed32(48), to_fixed32(248) }, /* bottom */
    { to_fixed32(88), to_fixed32(136), to_fixed32(56) }, /* top */
  };
  std::vector<EnemigoFuego> enemies;

  void initPlatforms();
  void initLadders();
  void initHammers();

  void addEnemies(unsigned int amount);
  void checkCollisions();
};

#endif// NIVEL_1_H
