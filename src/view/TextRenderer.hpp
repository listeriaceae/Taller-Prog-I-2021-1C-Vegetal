#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string_view>
#include "../utils/punto.hpp"

enum Color { YELLOW, RED, WHITE, CYAN, LIME, MAGENTA, BLUE };

namespace TextRenderer {
constexpr std::string_view
available_chars()
{
  return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.- ";
}
constexpr bool
includesCharacter(char character)
{
  return available_chars().find_first_of(character) != std::string_view::npos;
}

void renderText(punto<int> punto,
                std::string_view text,
                float resize,
                enum Color color = Color::YELLOW);
}// namespace TextRenderer

#endif// TEXT_RENDERER_H
