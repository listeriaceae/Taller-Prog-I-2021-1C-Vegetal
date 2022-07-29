#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.hpp"
#include "mario/MuriendoState.hpp"

Mario::Mario() : state{ SueloState::getInstance() } {}

void Mario::setStageAndReset(Stage *stage)
{
  MarioState::resetStage(stage);
  this->reset();
}

void Mario::mover()
{
  auto old = controls.fetch_and(~SPACE, std::memory_order_relaxed);
  this->state->update(*this, old);
}

void Mario::die()
{
  if (ticks_dead != 0) return;
  ++ticks_dead;
  --lives;
  this->audioObserver.update(DEATH);
  this->state = MuriendoState::getInstance();
}
