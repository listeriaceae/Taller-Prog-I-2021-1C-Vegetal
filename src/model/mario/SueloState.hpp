#ifndef SUELO_STATE_H
#define SUELO_STATE_H

#include "MarioState.hpp"

class SueloState : public MarioState
{
public:
  void update(Mario &mario, std::uint8_t) const override;
  static const SueloState *getInstance();

private:
  SueloState() = default;
  static const SueloState instance;
};

#endif// SUELO_STATE_H
