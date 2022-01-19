#ifndef BARRIL_VISTA_H
#define BARRIL_VISTA_H

#include "../utils/punto.hpp"

class BarrilVista
{
public:
  constexpr void startRender() { update = 1; };
  void mostrar(punto16_t pos);

private:
  int tiempo{};
  int update{};
};

#endif// BARRIL_VISTA_H
