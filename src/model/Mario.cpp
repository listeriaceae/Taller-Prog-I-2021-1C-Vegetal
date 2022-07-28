#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.hpp"
#include "mario/MuriendoState.hpp"
#include "collider/NormalCollider.hpp"
#include "collider/HammerCollider.hpp"


Mario::Mario()
  : collider{ NormalCollider::getInstance() }, state{ SueloState::getInstance() }
{
}

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
  if (contador != 0)
    return;
  ++contador;
  --lives;
  this->audioObserver.update(DEATH);
  this->state = MuriendoState::getInstance();
}

void Mario::collide(Hammer &hammer)
{
  this->collider = HammerCollider::getInstance();
  hammer.consume();
  hammerUses = 3;
  this->audioObserver.update(ITEM);
}
