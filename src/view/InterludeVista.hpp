#ifndef INTERLUDE_VISTA_H
#define INTERLUDE_VISTA_H

#include "SceneVista.hpp"
#include <cstddef>

class InterludeVista : public SceneVista
{
public:
  InterludeVista();
  void update(const GameState &state) override;

private:
  std::size_t maxPlayers;
};

#endif// INTERLUDE_VISTA_H
