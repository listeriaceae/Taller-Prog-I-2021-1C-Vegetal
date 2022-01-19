#include "Nivel2.hpp"
#include "../utils/Constants.hpp"
#include <random>
#include <algorithm>

Nivel2::Nivel2(std::vector<Mario> *players_) : Nivel{ players_ }
{
  initPlatforms();
  initLadders();
  initHammers();
  barriles.reserve(MAX_BARRELS);
}

void Nivel2::initPlatforms()
{
  for (const auto &platform : platforms)
    stage.addPlatform(&platform);
}

void Nivel2::initLadders()
{
  stage.addLadder({ to_fixed32(180), to_fixed32(203.25f), to_fixed32(227.75f) });
  stage.addLadder({ to_fixed32(92), to_fixed32(167.25f), to_fixed32(197.75f) });
  stage.addLadder({ to_fixed32(28), to_fixed32(171.25f), to_fixed32(193.75f) });
  stage.addLadder({ to_fixed32(108), to_fixed32(132.75f), to_fixed32(166.25f) });
  stage.addLadder({ to_fixed32(180), to_fixed32(137.25f), to_fixed32(161.75f) });
  stage.addLadder({ to_fixed32(68), to_fixed32(102.75f), to_fixed32(130.25f) });
  stage.addLadder({ to_fixed32(28), to_fixed32(105.25f), to_fixed32(127.75f) });
  stage.addLadder({ to_fixed32(180), to_fixed32(71.25f), to_fixed32(95.75f) });
  stage.addLadder({ to_fixed32(124), to_fixed32(40), to_fixed32(68) });
}

void Nivel2::initHammers()
{
  std::mt19937 mt{ std::random_device{}() };
  std::uniform_int_distribution<int> int_rng{ 0, 3 };
  std::uniform_int_distribution<fixed32_t> fixed32_rng{ 0, to_fixed32(3) };
  for (int i = 0; i < MAX_HAMMERS; ++i) {
    const int n = int_rng(mt);
    const fixed32_t t = fixed32_rng(mt);
    hammers.emplace_back(punto32_t{
      to_fixed32(104) + (n % 2 ? 1 : -1) * (to_fixed32(48) + 16 * t),
      to_fixed32(84) + to_fixed32(33) * n + t });
  }
}

void Nivel2::update()
{
  static constexpr size_t period = 180;
  if (++tick % period == 1)
    barriles.emplace_back();

  for (auto &barril : barriles)
    barril.mover();
  for (auto &mario : *players)
    mario.mover();
  erase_out_of_bounds();
  checkCollisions();
}

static inline std::array<punto16_t, MAX_BARRELS>
  to_array(const std::vector<Barril> &in)
{
  std::array<punto16_t, MAX_BARRELS> out{};
  std::transform(std::cbegin(in), std::cend(in), std::begin(out), get_pos<Entidad>);
  return out;
}

LevelState
  Nivel2::getEstado() const
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

  l_state.v = to_array(barriles);

  return l_state;
}

void Nivel2::checkCollisions()
{
  for (Mario &player : *players) {
    const auto player_dimensions = player.get_dimensions();
    for (auto it = barriles.begin(); it != barriles.end();) {
      if (intersect(player_dimensions, it->get_dimensions())) {
        if (player.collide(*it))
          it = barriles.erase(it);
        else
          break;
      } else
        ++it;
    }

    for (auto &hammer : this->hammers) {
      if (intersect(player_dimensions, hammer.get_dimensions()))
        player.collide(hammer);
    }
  }
}

void Nivel2::erase_out_of_bounds()
{
  for (auto it = barriles.begin(); it != barriles.end();) {
    if (it->out_of_bounds()) {
      it = barriles.erase(it);
    } else {
      ++it;
    }
  }
}
