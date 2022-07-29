#include "SueloState.hpp"
#include "AireState.hpp"
#include "TrepandoState.hpp"
#include "../Mario.hpp"
#include "../../utils/Constants.hpp"

static constexpr int sign(fixed32_t x) noexcept { return (0 < x) - (x < 0); }

const SueloState SueloState::instance{};

const SueloState *SueloState::getInstance() { return &instance; }

void SueloState::update(Mario &mario, std::uint8_t controls) const
{
  {
    const int y_direction = ((controls & UP) >> 1) - ((controls & DOWN) >> 2);
    if (const auto ladder =
          stage->getLadder(mario.pos.x, mario.pos.y, y_direction);
        ladder.has_value()) {
      if (const auto distance = ladder->x - mario.pos.x;
          to_fixed32(-4) <= distance && distance <= to_fixed32(4)) {
        mario.pos.x = ladder->x;
        mario.pos.y -= y_direction * climb_speed;
        mario.climbMin = ladder->bottom;
        mario.climbMax = ladder->top;
        mario.state = TrepandoState::getInstance();
        return;
      }
    }
  }
  mario.vel.x =
    (((controls & RIGHT) >> 4) - ((controls & LEFT) >> 3)) * x_speed;
  mario.vel.y = to_fixed32(-1);
  mario.pos.x +=
    mario.vel.x
    * ((mario.pos.x < to_fixed32(ANCHO_NIVEL - ANCHO_MARIO) && 0 < mario.vel.x)
       || (0 < mario.pos.x && mario.vel.x < 0));
  mario.pos.y -= mario.vel.y;
  if (controls & SPACE) {
    mario.vel.y = jump_speed;
    mario.audioObserver.update(JUMP);
    mario.state = AireState::getInstance();
  } else if (!stage->collide(
               mario.pos.x, mario.pos.y, mario.vel.x, mario.vel.y)) {
    mario.vel = {};
    mario.state = AireState::getInstance();
  } else {
    switch (sign(mario.vel.x)) {
    case -1:
      mario.direccion = Direccion::IZQUIERDA;
      mario.estado = Estado::CORRIENDO;
      break;
    case 1:
      mario.direccion = Direccion::DERECHA;
      mario.estado = Estado::CORRIENDO;
      break;
    default:
      mario.estado = mario.estado == Estado::DE_ESPALDAS ? Estado::DE_ESPALDAS
                                                         : Estado::REPOSO;
      break;
    }
  }
}
