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
  std::array<Platform, 18> platforms{
    Platform{ to_fixed32(64.f), to_fixed32(248.f), to_fixed32(88.f), to_fixed32(248.f) },
    { to_fixed32(104.f), to_fixed32(248.f), to_fixed32(128.f), to_fixed32(248.f) },
    { to_fixed32(144.f), to_fixed32(248.f), to_fixed32(168.f), to_fixed32(248.f) },
    { to_fixed32(184.f), to_fixed32(248.f), to_fixed32(224.f), to_fixed32(248.f) },
    { to_fixed32(0.f), to_fixed32(200.f), to_fixed32(48.f), to_fixed32(200.f) },
    { to_fixed32(64.f), to_fixed32(200.f), to_fixed32(88.f), to_fixed32(200.f) },
    { to_fixed32(104.f), to_fixed32(200.f), to_fixed32(128.f), to_fixed32(200.f) },
    { to_fixed32(144.f), to_fixed32(200.f), to_fixed32(168.f), to_fixed32(200.f) },
    { to_fixed32(184.f), to_fixed32(200.f), to_fixed32(224.f), to_fixed32(200.f) },
    { to_fixed32(160.f), to_fixed32(87.f), to_fixed32(192.f), to_fixed32(87.f) },
    { to_fixed32(24.f), to_fixed32(84.f), to_fixed32(144.f), to_fixed32(84.f) },
    { to_fixed32(0.f), to_fixed32(160.f), to_fixed32(16.f), to_fixed32(160.f) },
    { to_fixed32(208.f), to_fixed32(160.f), to_fixed32(224.f), to_fixed32(160.f) },
    { to_fixed32(0.f), to_fixed32(120.f), to_fixed32(16.f), to_fixed32(120.f) },
    { to_fixed32(208.f), to_fixed32(120.f), to_fixed32(224.f), to_fixed32(120.f) },
    { to_fixed32(208.f), to_fixed32(88.f), to_fixed32(224.f), to_fixed32(88.f) },
    { to_fixed32(0.f), to_fixed32(248.f), to_fixed32(48.f), to_fixed32(248.f) },// bottom
    { to_fixed32(88.f), to_fixed32(56.f), to_fixed32(135.f), to_fixed32(56.f) }// top
  };
  std::vector<EnemigoFuego> enemies;

  void initPlatforms();
  void initLadders();
  void initHammers();

  void addEnemies(unsigned int amount);
  void checkCollisions();
};

#endif// NIVEL_1_H
