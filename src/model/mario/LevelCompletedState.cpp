#include "LevelCompletedState.hpp"
#include "../Mario.hpp"

const LevelCompletedState LevelCompletedState::instance{};

const LevelCompletedState *
  LevelCompletedState::getInstance()
{
  return &instance;
}

bool LevelCompletedState::isPlaying() const
{
  return false;
}

void LevelCompletedState::update(Mario &mario, std::uint8_t) const
{
  mario.estado = Estado::NIVEL_COMPLETO;
}
