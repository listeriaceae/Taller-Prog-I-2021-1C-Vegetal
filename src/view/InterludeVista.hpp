#ifndef INTERLUDE_VISTA_H
#define INTERLUDE_VISTA_H

#include "SceneVista.hpp"

class InterludeVista : public SceneVista
{
public:
  InterludeVista();
  void update(const GameState &state) override;

private:
  unsigned int maxPlayers;
};

#endif// INTERLUDE_VISTA_H
