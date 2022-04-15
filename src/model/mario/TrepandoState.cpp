#include "SueloState.hpp"
#include "TrepandoState.hpp"
#include "LevelCompletedState.hpp"
#include "../Mario.hpp"

const TrepandoState TrepandoState::instance{};

const TrepandoState *
  TrepandoState::getInstance()
{
  return &instance;
}

void TrepandoState::update(Mario &mario, std::uint8_t controls) const
{
  mario.vel.y =
    (((controls & UP) >> 1) - ((controls & DOWN) >> 2)) * climb_speed;
  if (mario.pos.y == mario.climbMin || mario.pos.y == mario.climbMax) {
    if ( mario.pos.y == to_fixed32(TOP_LEVEL)) {
      mario.resetCollider();
      mario.audioObserver.update(FINISHED_LEVEL);
      mario.score += points * 5;
      mario.pos.x -= (4 - points) * to_fixed32(13);
      points -= 1;
      mario.state = LevelCompletedState::getInstance();
    } else {
      mario.estado = Estado::DE_ESPALDAS;
      mario.state = SueloState::getInstance();
    }
  } else {
    mario.pos.y -= mario.vel.y;
    mario.estado = Estado::TREPANDO;
  }
}
