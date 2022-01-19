#ifndef GAME_OVER_SATTE_H
#define GAME_OVER_STATE_H

#include "MarioState.hpp"

class GameOverState : public MarioState
{
public:
  void update(Mario &mario, std::uint8_t) const override;
  void reset(Mario &) const override;
  bool isAlive() const override;
  bool isPlaying() const override;
  static const GameOverState *getInstance();

private:
  GameOverState() = default;
  static const GameOverState instance;
};

#endif// GAME_OVER_STATE_H
