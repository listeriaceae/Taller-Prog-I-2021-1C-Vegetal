#include <algorithm>
#include <fmt/format.h>
#include <fstream>
#include <json/json.h>
#include <stdexcept>

#include "configuration.hpp"
#include "logger.hpp"

namespace configuration {
static Enemy::Type
from_string(const std::string &t) {
  if (t == "Fuego")
    return Enemy::Type::FUEGO;
  else
    throw std::runtime_error(fmt::format("Unknown enemy: '{}'", t));
}

Enemy::Enemy(const std::string &t, unsigned int q)
: type{ from_string(t) }, quantity{ q } {}

static Json::Value config;
static Json::Value getJsonValue(const Json::Value &root, std::string name);

template<typename Ret, typename Callable>
Ret
try_or_default(Callable f, Ret dfl)
{
  try {
    return f();
  } catch (const std::exception &e) {
    logger::logError(e.what());

    return dfl;
  }
}

logger::LogLevel
getLogLevel()
{
  auto f = []() -> logger::LogLevel {
    const auto logString = getJsonValue(config, "logLevel").asString();
    if (logString == "ERROR")
      return logger::LogLevel::ERROR;
    else if (logString == "INFO")
      return logger::LogLevel::INFO;
    else if (logString == "DEBUG")
      return logger::LogLevel::DEBUG;
    else
      throw std::runtime_error(fmt::format("Unknown log level: '{}'", logString));
  };

  return try_or_default(f, logger::LogLevel::DEBUG);
}

std::size_t
getMaxPlayers()
{
  auto f = []() -> std::size_t {
    const auto maxPlayers = getJsonValue(config, "players").asLargestUInt();
    if (0 < maxPlayers && maxPlayers <= 4)
      return maxPlayers;
    else
      throw std::runtime_error("Number of players must be between 1 and 4");
  };

  return try_or_default(f, 1ul);
}

std::vector<Enemy>
getEnemies()
{
  auto f = []() -> std::vector<Enemy> {
    const auto enemiesJSON = getJsonValue(config, "enemies");
    std::vector<Enemy> out(enemiesJSON.size());
    std::transform(std::begin(enemiesJSON), std::end(enemiesJSON), std::begin(out),
      [](auto e) {
	return Enemy{ getJsonValue(e, "type").asString(),
		      getJsonValue(e, "quantity").asUInt() };
      });
    return out;
  };

  return try_or_default(f, std::vector<Enemy>{ Enemy{ "Fuego", 3u } });
}

std::vector<std::pair<std::string, std::string>>
getUsers()
{
  auto f = []() -> std::vector<std::pair<std::string, std::string>> {
    const auto usersJSON = getJsonValue(config, "users");
    std::vector<std::pair<std::string, std::string>> out(usersJSON.size());
    std::transform(std::begin(usersJSON), std::end(usersJSON), std::begin(out),
      [](auto u) { return std::make_pair(getJsonValue(u, "username").asString(),
					 getJsonValue(u, "password").asString());
      });
    return out;
  };

  return try_or_default(f, std::vector<std::pair<std::string, std::string>>{
			    std::make_pair("U1", ""),
			    std::make_pair("U2", ""),
			    std::make_pair("U3", ""),
			    std::make_pair("U4", ""),
			   });
}

void
init(const char *configPath)
{
  try {
    std::ifstream{ configPath } >> config;
  } catch (const std::exception &e) {
    logger::logError(e.what());
  }
}

Json::Value
getJsonValue(const Json::Value &root, std::string name)
{
  const auto value = root[name];
  if (value.empty())
    throw std::runtime_error(fmt::format("JSON value not found: '{}'", name));
  return value;
}
}// namespace configuration
