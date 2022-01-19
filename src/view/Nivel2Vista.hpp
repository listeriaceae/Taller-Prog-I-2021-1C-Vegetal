#ifndef NIVEL_2_VISTA_H
#define NIVEL_2_VISTA_H

#include "NivelVista.hpp"
#include "BarrilVista.hpp"
#include "FuegoVista.hpp"

class Nivel2Vista : public NivelVista
{
public:
  Nivel2Vista(std::size_t playerIndex);
  void update(const GameState &estadoJuego) override;

private:
  FuegoVista fuegoVista;
  BarrilVista barrilVista;
};

#endif// NIVEL_2_VISTA_H
