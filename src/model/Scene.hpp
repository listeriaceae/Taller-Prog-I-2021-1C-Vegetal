#ifndef SCENE_H
#define SCENE_H

#include "../utils/estadoJuego.hpp"

/* Representa a todas las clases que conocen el estado del nivel */
class Scene
{
public:
  virtual void update() = 0;
  virtual LevelState getEstado() const = 0;
  virtual bool isComplete() const = 0;
  virtual ~Scene() = default;
};

#endif// SCENE_H
