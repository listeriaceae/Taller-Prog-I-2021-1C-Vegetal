#ifndef NIVEL_H
#define NIVEL_H

#include <vector>
#include <array>
#include <algorithm>
#include "Scene.hpp"
#include "stage/Stage.hpp"
#include "Mario.hpp"
#include "Hammer.hpp"

/* Representa un nivel del juego, contiene a Stage (plataformas y escaleras) */
class Nivel : public Scene
{
public:
  Nivel(std::vector<Mario> *players_) : Scene{}, players{ players_ }
  {
    for (auto &player : *players) player.setStageAndReset(&stage);
  }
  [[nodiscard]] bool isComplete() const noexcept override
  {
    return std::none_of(players->cbegin(), players->cend(), &isPlaying);
  }

protected:
  Stage stage;
  std::vector<Hammer> hammers;
  std::vector<Mario> *players;
};

#endif// NIVEL_H
