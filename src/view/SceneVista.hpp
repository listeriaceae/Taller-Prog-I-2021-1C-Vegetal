#ifndef SCENE_VISTA_H
#define SCENE_VISTA_H

#include "../utils/estadoJuego.hpp"

/* Interfaz que representa cualquier escena que se puede mostrar al cliente */
class SceneVista
{
public:
  virtual ~SceneVista() = default;
  virtual void update(const GameState &estadoJuego) = 0;
};

#endif// SCENE_VISTA_H
