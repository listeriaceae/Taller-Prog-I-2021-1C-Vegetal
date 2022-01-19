#ifndef TREPANDO_STATE_H
#define TREPANDO_STATE_H

#include "MarioState.hpp"

class TrepandoState : public MarioState
{
public:
  void update(Mario &mario, std::uint8_t) const override;
  static const TrepandoState *getInstance();

private:
  TrepandoState() = default;
  static const TrepandoState instance;
};

#endif// TREPANDO_STATE_H
