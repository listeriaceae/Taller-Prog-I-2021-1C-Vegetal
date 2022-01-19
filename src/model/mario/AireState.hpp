#ifndef AIRE_STATE_H
#define AIRE_STATE_H

#include "MarioState.hpp"

class AireState : public MarioState
{
public:
  void update(Mario &mario, std::uint8_t) const override;
  static const AireState *getInstance();

private:
  AireState() = default;
  static const AireState instance;
};

#endif// AIRE_STATE_H
