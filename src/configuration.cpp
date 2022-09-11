#include <algorithm>
#include <fmt/format.h>
#include <fstream>
#include <json/json.h>

#include "configuration.hpp"
#include "logger.hpp"

namespace configuration {
static Json::Value config;

logger::LogLevel
getLogLevel()
{
  const auto logString = config.get("log", "debug").asString();
  if (logString == "error")
    return logger::LogLevel::ERROR;
  else if (logString == "info")
    return logger::LogLevel::INFO;
  else
    return logger::LogLevel::DEBUG;
}

unsigned int
getMaxPlayers()
{
  const auto maxPlayers = config.get("players", 1).asUInt();
  if (0 < maxPlayers && maxPlayers <= 4)
    return std::min(maxPlayers, std::max(config["users"].size(), 1u));
  else
    return 1;
}

std::size_t
getFireEnemies()
{
  return config["enemies"].get("fire", 3).asLargestUInt();
}

std::size_t
getBarrelFrequency()
{
  return config["enemies"].get("barrels", 180).asLargestUInt();
}

std::vector<std::pair<std::string, std::string>>
getUsers()
{
  std::vector<std::pair<std::string, std::string>> out;

  for (auto i = 1; const auto &user : config["users"]) {
    const auto &name = user["username"];
    const auto &pass = user["password"];
    if (name.isString() && pass.isString())
      out.emplace_back(name.asString(), pass.asString());
    else
      out.emplace_back(fmt::format("USER{}", i++), "PASS");
  }

  return out.empty() ? std::vector<std::pair<std::string, std::string>>{std::make_pair("USER1", "PASS")} : out;
}

void
init(const char *filename)
{
  if (auto ifs = std::ifstream(filename); ifs.good())
    ifs >> config;
  else
    logger::logError(fmt::format("failed to read '{}'", filename));
}
}// namespace configuration
