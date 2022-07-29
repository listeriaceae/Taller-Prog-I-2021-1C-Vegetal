#include "GameOverState.hpp"
#include "../Mario.hpp"

const GameOverState GameOverState::instance{};

const GameOverState *
GameOverState::getInstance()
{
  return &instance;
}

void
GameOverState::reset(Mario &) const
{}

bool
GameOverState::isAlive() const
{
  return false;
}

bool
GameOverState::isPlaying() const
{
  return false;
}

void
GameOverState::update(Mario &mario, std::uint8_t) const
{
  mario.estado = Estado::GAME_OVER;
}
