#ifndef MARIO_H
#define MARIO_H

#include <atomic>
#include "mario/MarioState.hpp"
#include "mario/AudioObserver.hpp"
#include "../utils/marioStructs.hpp"
#include "../utils/punto.hpp"
#include "Entidad.hpp"
#include "Hammer.hpp"

class Mario
{
public:
  Mario();
  inline void reset()
  {
    state->reset(*this);
    hammerUses = 0;
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
    static constexpr auto width = to_fixed32(ANCHO_MARIO);
    static constexpr auto height = to_fixed32(ALTO_MARIO);
    static constexpr auto x_diff = to_fixed32(3);
    static constexpr auto y_diff = to_fixed32(2);

    return { pos.x + x_diff,
      pos.y + y_diff,
      pos.x + (width - x_diff),
      pos.y + (height - y_diff) };
  }
  template<typename E> inline bool collide(const E &enemy)
  {
    if (hammerUses > 0 && hammerHit(enemy)) {
      --hammerUses;
      audioObserver.update(ENEMY_DEATH);
      score += enemy.points;
      return true;
    } else {
      die();
      return false;
    }
  }
  void grabHammer()
  {
    hammerUses = 3;
    audioObserver.update(ITEM);
  }

  punto32_t pos{};
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
  std::uint8_t ticks_dead{ 0 };
  std::int8_t hammerUses{ 0 };
  std::atomic<std::uint8_t> controls{ 0 };

private:
  template<typename E> bool hammerHit(const E &enemy) const
  {
    const bool collidedWithHammer =
      ((direccion == Direccion::DERECHA) && (pos.x < enemy.pos.x))
      || ((direccion == Direccion::IZQUIERDA) && (pos.x >= enemy.pos.x));

    return estado <= Estado::CORRIENDO && collidedWithHammer;
  }
};

inline bool isPlaying(const Mario &mario) noexcept
{
  return mario.isEnabled && mario.state->isPlaying();
}
inline bool isAlive(const Mario &mario) noexcept
{
  return mario.isEnabled && mario.state->isAlive();
}

inline PlayerState get_state(const Mario &m) noexcept
{
  return { get_pos(m),
    m.isEnabled,
    m.estado,
    m.audioObserver.getState(),
    m.hammerUses > 0 ? ColliderType::HAMMER : ColliderType::NORMAL };
}

#endif// MARIO_H
