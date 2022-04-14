#include "DefaultConfigVista.hpp"
#include "TextRenderer.hpp"
#include "../utils/Constants.hpp"

void DefaultConfigVista::mostrar()
{
  TextRenderer::renderText({ DEFAULT_CONFIG_X, DEFAULT_CONFIG_Y },
                           "DEFAULT CONFIG",
                           1,
                           Color::RED);
}
