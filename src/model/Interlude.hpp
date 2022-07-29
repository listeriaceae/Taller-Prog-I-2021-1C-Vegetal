#ifndef INTERLUDE_H
#define INTERLUDE_H

#include "Scene.hpp"

static constexpr size_t duration = 300;

class Interlude : public Scene
{
public:
  Interlude(bool gameOver_) : Scene{}, gameOver{ gameOver_ } {};
  void
  update() override
  {
    ++ticks;
  };
  LevelState
  getEstado() const override
  {
    return { {}, {}, gameOver };
  };
  bool
  isComplete() const override
  {
    return ticks > duration;
  };

private:
  size_t ticks{};
  bool gameOver;
};

#endif// INTERLUDE_H
