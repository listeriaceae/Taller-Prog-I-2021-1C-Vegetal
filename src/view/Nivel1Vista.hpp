#ifndef NIVEL_1_VISTA_H
#define NIVEL_1_VISTA_H

#include <array>
#include "NivelVista.hpp"
#include "EnemigoFuegoVista.hpp"
#include "PoleaVista.hpp"
#include "FuegoVista.hpp"

class Nivel1Vista : public NivelVista
{
public:
  Nivel1Vista(std::size_t playerIndex);
  void update(const GameState &estadoJuego) override;

private:
  std::array<PoleaVista, 4> poleas;
  std::array<FuegoVista, 4> fuegos;
  std::vector<EnemigoFuegoVista> enemigosVista;
};

#endif// NIVEL_1_VISTA_H
