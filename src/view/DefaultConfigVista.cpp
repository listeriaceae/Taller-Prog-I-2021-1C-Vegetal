#include "DefaultConfigVista.hpp"
#include "TextRenderer.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

void DefaultConfigVista::mostrar()
{
  TextRenderer::renderText(
    { static_cast<int>(DEFAULT_CONFIG_X * ANCHO_PANTALLA / (float)ANCHO_NIVEL),
      static_cast<int>(DEFAULT_CONFIG_Y * ALTO_PANTALLA / (float)ALTO_NIVEL) },
    "DEFAULT CONFIG",
    1,
    Color::RED);
}
