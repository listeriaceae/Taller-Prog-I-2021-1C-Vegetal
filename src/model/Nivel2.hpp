#ifndef NIVEL_2_H
#define NIVEL_2_H

#include "Nivel.hpp"
#include "Barril.hpp"

class Nivel2 : public Nivel
{
public:
  Nivel2(std::vector<Mario> *players);
  void update() override;
  LevelState getEstado() const override;

private:
  std::vector<Barril> barriles;
  size_t tick = 0;

  void initPlatforms();
  void initLadders();
  void initHammers();

  void checkCollisions();
  std::vector<Barril>::iterator
  erase_out_of_bounds(std::vector<Barril>::iterator it);

private:
  static constexpr std::array<Platform, 66> platforms{
    Platform{ to_fixed32(0), to_fixed32(112), to_fixed32(248) },
    { to_fixed32(112), to_fixed32(128), to_fixed32(247) },
    { to_fixed32(128), to_fixed32(144), to_fixed32(246) },
    { to_fixed32(144), to_fixed32(160), to_fixed32(245) },
    { to_fixed32(160), to_fixed32(176), to_fixed32(244) },
    { to_fixed32(176), to_fixed32(192), to_fixed32(243) },
    { to_fixed32(192), to_fixed32(208), to_fixed32(242) },
    { to_fixed32(208), to_fixed32(224), to_fixed32(241) },
    { to_fixed32(192), to_fixed32(208), to_fixed32(220) },
    { to_fixed32(176), to_fixed32(192), to_fixed32(219) },
    { to_fixed32(160), to_fixed32(176), to_fixed32(218) },
    { to_fixed32(144), to_fixed32(160), to_fixed32(217) },
    { to_fixed32(128), to_fixed32(144), to_fixed32(216) },
    { to_fixed32(112), to_fixed32(128), to_fixed32(215) },
    { to_fixed32(96), to_fixed32(112), to_fixed32(214) },
    { to_fixed32(80), to_fixed32(96), to_fixed32(213) },
    { to_fixed32(64), to_fixed32(80), to_fixed32(212) },
    { to_fixed32(48), to_fixed32(64), to_fixed32(211) },
    { to_fixed32(32), to_fixed32(48), to_fixed32(210) },
    { to_fixed32(16), to_fixed32(32), to_fixed32(209) },
    { to_fixed32(0), to_fixed32(16), to_fixed32(208) },
    { to_fixed32(16), to_fixed32(32), to_fixed32(187) },
    { to_fixed32(32), to_fixed32(48), to_fixed32(186) },
    { to_fixed32(48), to_fixed32(64), to_fixed32(185) },
    { to_fixed32(64), to_fixed32(80), to_fixed32(184) },
    { to_fixed32(80), to_fixed32(96), to_fixed32(183) },
    { to_fixed32(96), to_fixed32(112), to_fixed32(182) },
    { to_fixed32(112), to_fixed32(128), to_fixed32(181) },
    { to_fixed32(128), to_fixed32(144), to_fixed32(180) },
    { to_fixed32(144), to_fixed32(160), to_fixed32(179) },
    { to_fixed32(160), to_fixed32(176), to_fixed32(178) },
    { to_fixed32(176), to_fixed32(192), to_fixed32(177) },
    { to_fixed32(192), to_fixed32(208), to_fixed32(176) },
    { to_fixed32(208), to_fixed32(224), to_fixed32(175) },
    { to_fixed32(192), to_fixed32(208), to_fixed32(154) },
    { to_fixed32(176), to_fixed32(192), to_fixed32(153) },
    { to_fixed32(160), to_fixed32(176), to_fixed32(152) },
    { to_fixed32(144), to_fixed32(160), to_fixed32(151) },
    { to_fixed32(128), to_fixed32(144), to_fixed32(150) },
    { to_fixed32(112), to_fixed32(128), to_fixed32(149) },
    { to_fixed32(96), to_fixed32(112), to_fixed32(148) },
    { to_fixed32(80), to_fixed32(96), to_fixed32(147) },
    { to_fixed32(64), to_fixed32(80), to_fixed32(146) },
    { to_fixed32(48), to_fixed32(64), to_fixed32(145) },
    { to_fixed32(32), to_fixed32(48), to_fixed32(144) },
    { to_fixed32(16), to_fixed32(32), to_fixed32(143) },
    { to_fixed32(0), to_fixed32(16), to_fixed32(142) },
    { to_fixed32(16), to_fixed32(32), to_fixed32(121) },
    { to_fixed32(32), to_fixed32(48), to_fixed32(120) },
    { to_fixed32(48), to_fixed32(64), to_fixed32(119) },
    { to_fixed32(64), to_fixed32(80), to_fixed32(118) },
    { to_fixed32(80), to_fixed32(96), to_fixed32(117) },
    { to_fixed32(96), to_fixed32(112), to_fixed32(116) },
    { to_fixed32(112), to_fixed32(128), to_fixed32(115) },
    { to_fixed32(128), to_fixed32(144), to_fixed32(114) },
    { to_fixed32(144), to_fixed32(160), to_fixed32(113) },
    { to_fixed32(160), to_fixed32(176), to_fixed32(112) },
    { to_fixed32(176), to_fixed32(192), to_fixed32(111) },
    { to_fixed32(192), to_fixed32(208), to_fixed32(110) },
    { to_fixed32(208), to_fixed32(224), to_fixed32(109) },
    { to_fixed32(192), to_fixed32(208), to_fixed32(88) },
    { to_fixed32(176), to_fixed32(192), to_fixed32(87) },
    { to_fixed32(160), to_fixed32(176), to_fixed32(86) },
    { to_fixed32(144), to_fixed32(160), to_fixed32(85) },
    { to_fixed32(0), to_fixed32(144), to_fixed32(84) },
    { to_fixed32(88), to_fixed32(136), to_fixed32(56) }, /* top */
  };
};

#endif// NIVEL_2_H
