#include "MuriendoState.hpp"
#include "GameOverState.hpp"
#include "SueloState.hpp"
#include "../Mario.hpp"

const MuriendoState MuriendoState::instance{};

const MuriendoState *
  MuriendoState::getInstance()
{
  return &instance;
}

void MuriendoState::reset(Mario &mario) const
{
  if (0 < mario.lives) {
    MarioState::reset(mario);
  } else {
    mario.state = GameOverState::getInstance();
  }
}

void MuriendoState::update(Mario &mario, std::uint8_t) const
{
  ++mario.contador;
  if (static constexpr decltype(mario.contador) respawn_ticks = 180;
      mario.contador > respawn_ticks) {
    if (mario.lives == 0) {
      mario.state = GameOverState::getInstance();
    } else {
      mario.contador = 0;
      mario.reset();
      mario.state = SueloState::getInstance();
    }
  } else {
    static constexpr decltype(mario.contador) dying_ticks = 90;
    mario.estado = mario.contador < dying_ticks ? Estado::MURIENDO : Estado::MUERTO;
  }
}
