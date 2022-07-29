#include "AireState.hpp"
#include "SueloState.hpp"
#include "MuriendoState.hpp"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"

const AireState AireState::instance{};

const AireState *AireState::getInstance() { return &instance; }

void AireState::update(Mario &mario, std::uint8_t) const
{
  mario.estado = mario.vel.y > 0 ? Estado::SALTANDO : mario.estado;
  mario.vel.x -=
    mario.vel.x * 2
    * !((mario.pos.x < to_fixed32(ANCHO_NIVEL - ANCHO_MARIO) && 0 < mario.vel.x)
        || (0 < mario.pos.x && mario.vel.x < 0));
  mario.vel.y += g;
  mario.pos.x += mario.vel.x;
  mario.pos.y -= mario.vel.y;
  if (stage->collide(mario.pos.x, mario.pos.y, mario.vel.x, mario.vel.y))
    mario.state = SueloState::getInstance();
  else if (mario.pos.y > to_fixed32(ALTO_NIVEL - ALTO_MARIO))
    mario.die();
}
