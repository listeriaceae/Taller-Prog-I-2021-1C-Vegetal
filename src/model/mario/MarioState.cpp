#include "MarioState.hpp"
#include "SueloState.hpp"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"

const Stage *MarioState::stage{ nullptr };
unsigned char MarioState::points{ 4 };

void MarioState::reset(Mario &mario) const
{
  mario.pos = { to_fixed32(MARIO_START_X), to_fixed32(MARIO_START_Y) };
  mario.estado = Estado::REPOSO;
  mario.state = SueloState::getInstance();
}

bool MarioState::isPlaying() const { return true; }

bool MarioState::isAlive() const { return true; }

void MarioState::resetStage(const Stage *stage_)
{
  stage = stage_;
  points = 4;
}
