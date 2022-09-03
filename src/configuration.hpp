#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <utility>
#include <vector>
#include <fmt/format.h>

namespace logger {
enum class LogLevel;
}

namespace configuration {
class Enemy
{
public:
  enum class Type { FUEGO };
  Enemy() = default;
  Enemy(const std::string &t, unsigned int q);

  Type type;
  unsigned int quantity;
};

void init(const char *configPath);

logger::LogLevel getLogLevel();
std::size_t getMaxPlayers();
std::vector<Enemy> getEnemies();
std::vector<std::pair<std::string, std::string>> getUsers();
}// namespace configuration

template<>
struct fmt::formatter<configuration::Enemy::Type>
{
  constexpr auto
  parse(format_parse_context &ctx) -> decltype(ctx.begin())
  {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end)
      throw format_error("invalid format");
    return it;
  }

  template<typename FormatContext>
  auto
  format(configuration::Enemy::Type t, FormatContext &ctx)
  {
    switch (t) {
    case configuration::Enemy::Type::FUEGO:
      return fmt::format_to(ctx.out(), "Fuego");
    default:
      return fmt::format_to(ctx.out(), "Unknown");
    }
  }
};

#endif// CONFIGURATION_H
