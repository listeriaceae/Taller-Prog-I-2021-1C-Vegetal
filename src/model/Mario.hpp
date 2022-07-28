#ifndef MARIO_H
#define MARIO_H

#include <atomic>
#include "mario/MarioState.hpp"
#include "collider/NormalCollider.hpp"
#include "mario/AudioObserver.hpp"
#include "../utils/marioStructs.hpp"
#include "../utils/punto.hpp"
#include "Hammer.hpp"
#include "Enemy.hpp"

class Mario
{
public:
  Mario();
  inline void reset()
  {
    this->state->reset(*this);
    this->collider = NormalCollider::getInstance();
  }
  void setStageAndReset(Stage *stage);
  void mover();
  void die();
  inline void disable()
  {
    isEnabled = false;
    controls = {};
  }
  inline void enable() { isEnabled = true; }
  inline dimensions get_dimensions() const
  {
    return {
      pos.x + x_diff,
      pos.y + y_diff,
      pos.x + (width - x_diff),
      pos.y + (height - y_diff)
    };
  }
  inline void resetCollider() { this->collider = NormalCollider::getInstance(); }
  inline bool collide(Enemy &enemy) { return this->collider->collide(*this, enemy); }
  void collide(Hammer &hammer);

  punto32_t pos{};
  const Collider *collider;
  const MarioState *state;
  punto32_t vel{};
  fixed32_t climbMin{};
  fixed32_t climbMax{};
  Direccion direccion{ Direccion::DERECHA };
  bool isEnabled{ true };
  std::int8_t lives{ MARIO_LIVES };
  Estado estado{ Estado::REPOSO };
  AudioObserver audioObserver{};
  std::uint8_t score{ 0 };
  std::uint8_t contador{ 0 };
  std::int8_t hammerUses{ 0 };
  std::atomic<std::uint8_t> controls{ 0 };

private:
  static constexpr auto width = to_fixed32(ANCHO_MARIO);
  static constexpr auto height = to_fixed32(ALTO_MARIO);
  static constexpr auto x_diff = to_fixed32(3);
  static constexpr auto y_diff = to_fixed32(2);
};

inline bool
  isPlaying(const Mario &mario) noexcept
{
  return mario.isEnabled && mario.state->isPlaying();
}
inline bool
  isAlive(const Mario &mario) noexcept
{
  return mario.isEnabled && mario.state->isAlive();
}

inline PlayerState
  get_state(const Mario &m) noexcept
{
  return { { static_cast<fixed16_t>(m.pos.x), static_cast<fixed16_t>(m.pos.y) },
    m.isEnabled,
    m.estado,
    m.audioObserver.getState(),
    m.collider->getType() };
}

#endif// MARIO_H
