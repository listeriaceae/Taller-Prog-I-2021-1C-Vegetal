#ifndef MURIENDO_STATE_H
#define MURIENDO_STATE_H

#include "MarioState.hpp"

class MuriendoState : public MarioState
{
public:
  void update(Mario &mario, std::uint8_t controls) const override;
  void reset(Mario &mario) const override;
  static const MuriendoState *getInstance();

private:
  MuriendoState() = default;
  static const MuriendoState instance;
};

#endif// MURIENDO_STATE_H
