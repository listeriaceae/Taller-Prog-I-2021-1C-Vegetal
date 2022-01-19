#ifndef MARIO_STATE_H
#define MARIO_STATE_H

#include "../stage/Stage.hpp"

class Mario;

class MarioState
{
public:
  static void resetStage(const Stage *stage);
  virtual void reset(Mario &mario) const;
  virtual void update(Mario &mario, std::uint8_t) const = 0;
  virtual bool isPlaying() const;
  virtual bool isAlive() const;
  virtual ~MarioState() = default;

protected:
  static constexpr auto x_speed = to_fixed32(0.5);
  static constexpr auto climb_speed = to_fixed32(0.5);
  static constexpr auto jump_speed = to_fixed32(2);
  static constexpr decltype(jump_speed) g = -jump_speed / 16;
  MarioState() = default;
  static const Stage *stage;
  static unsigned char points;
};

#endif// MARIO_STATE_H
