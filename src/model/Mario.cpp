#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "mario/SueloState.hpp"
#include "mario/MuriendoState.hpp"
#include "collider/NormalCollider.hpp"
#include "collider/HammerCollider.hpp"


Mario::Mario()
  : Entidad{ {} }, collider{ NormalCollider::getInstance() }, state{ SueloState::getInstance() }
{
}

void Mario::setStageAndReset(Stage *stage)
{
  MarioState::resetStage(stage);
  this->reset();
}

void Mario::mover()
{
  std::uint8_t old = controls;
  {
    std::uint8_t aux = controls & ~SPACE;
    while (!controls.compare_exchange_weak(old, aux))
      aux = controls & ~SPACE;
  }
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
