#include <random>
#include <algorithm>
#include "Nivel1.hpp"
#include "Entidad.hpp"
#include "../configuration.hpp"
#include "../utils/Constants.hpp"

Nivel1::Nivel1(std::vector<Mario> *players_) : Nivel{ players_ }
{
  this->addEnemies(configuration::getFireEnemies());
  this->initPlatforms();
  this->initLadders();
  this->initHammers();
}

void
Nivel1::initPlatforms()
{
  for (const auto &mplatform : movingPlatforms)
    stage.addPlatform(&mplatform);

  for (const auto &platform : platforms)
    stage.addPlatform(&platform);
}

void
Nivel1::initLadders()
{
  stage.addLadder({ to_fixed32(28), to_fixed32(184), to_fixed32(232) });
  stage.addLadder({ to_fixed32(212), to_fixed32(144), to_fixed32(184) });
  stage.addLadder({ to_fixed32(-4), to_fixed32(104), to_fixed32(144) });
  stage.addLadder({ to_fixed32(212), to_fixed32(72), to_fixed32(104) });
  stage.addLadder({ to_fixed32(124), to_fixed32(40), to_fixed32(68) });
}

void
Nivel1::initHammers()
{
  std::mt19937 mt{ std::random_device{}() };
  std::uniform_int_distribution<fixed32_t> fixed32_rng{ to_fixed32(48),
                                                        to_fixed32(208) };
  for (int i = 0; i < MAX_HAMMERS; ++i)
    hammers.emplace_back(punto32_t{ fixed32_rng(mt), to_fixed32(208) });
}

void
Nivel1::addEnemies(std::size_t amount)
{
  std::mt19937 mt{ std::random_device{}() };
  std::uniform_int_distribution<std::size_t> index_rng{ 0, 10 };
  std::bernoulli_distribution bernoulli_rng;
  for (decltype(amount) i = 0; i < amount; ++i) {
    const auto j = index_rng(mt);
    const auto &platform = platforms[j];
    const auto pos = platform.getRandomPoint()
                     - punto32_t{ to_fixed32(ANCHO_ENEMIGO_FUEGO) / 2,
                                  to_fixed32(ALTO_ENEMIGO_FUEGO) };
    const int direccion = bernoulli_rng(mt) ? -1 : 1;
    const auto [min, max] = platform.getLimits();
    this->enemies.emplace_back(pos, direccion, min, max);
  }
}

void
Nivel1::update()
{
  for (auto &platform : movingPlatforms)
    platform.move();
  for (auto &enemy : enemies)
    enemy.mover();
  for (auto &mario : *players)
    mario.mover();
  checkCollisions();
}

static inline lv1
to_lv1(const std::array<MovingPlatform, 12UL> &mp,
       const std::vector<EnemigoFuego> &e)
{
  lv1 out{};
  std::transform(
    std::cbegin(mp), std::cend(mp), std::begin(out.platforms), get_start);

  std::transform(std::cbegin(e),
                 std::cend(e),
                 std::begin(out.enemies),
                 get_pos<EnemigoFuego>);

  return out;
}

LevelState
Nivel1::getEstado() const
{
  LevelState l_state{};

  std::transform(std::cbegin(hammers),
                 std::cend(hammers),
                 std::begin(l_state.hammers),
                 get_pos<Hammer>);

  std::transform(std::cbegin(*players),
                 std::cend(*players),
                 std::begin(l_state.players),
                 get_state);

  l_state.v = to_lv1(movingPlatforms, enemies);

  return l_state;
}

void
Nivel1::checkCollisions()
{
  for (Mario &player : *players) {
    const auto player_dimensions = player.get_dimensions();
    for (auto it = enemies.begin(); it != enemies.end();)
      if (intersect(player_dimensions, it->get_dimensions()))
        if (player.collide(*it))
          it = enemies.erase(it);
        else
          break;
      else
        ++it;

    for (auto &hammer : hammers)
      if (intersect(player_dimensions, hammer.get_dimensions())) {
        player.grabHammer();
        hammer.consume();
      }
  }
}
