#ifndef LEVEL_COMPLETE_STATE_H
#define LEVEL_COMPLETE_STATE_H
#include "MarioState.hpp"

class LevelCompletedState : public MarioState
{
public:
  void update(Mario &mario, std::uint8_t) const override;
  bool isPlaying() const override;
  static const LevelCompletedState *getInstance();

private:
  LevelCompletedState() = default;
  static const LevelCompletedState instance;
};

#endif// LEVEL_COMPLETE_STATE_H
