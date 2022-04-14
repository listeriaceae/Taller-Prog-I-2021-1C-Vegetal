#ifndef INTERLUDE_VISTA_H
#define INTERLUDE_VISTA_H

#include <cstddef>
#include "SceneVista.hpp"

class InterludeVista : public SceneVista
{
public:
  InterludeVista();
  void update(const GameState &state) override;

private:
  std::size_t maxPlayers;
};

#endif// INTERLUDE_VISTA_H
