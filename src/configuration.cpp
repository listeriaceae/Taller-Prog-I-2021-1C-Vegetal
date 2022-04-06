#include <iostream>
#include <fstream>
#include <cstring>
#include <fmt/format.h>
#include "configuration.hpp"
#include "logger.hpp"

namespace configuration {
const GameConfiguration &
  GameConfiguration::getInstance(const char *jsonFileName)
{
  static const GameConfiguration instance{ jsonFileName };
  return instance;
}

inline static bool
  exists(const char *filename)
{
  std::ifstream f(filename);
  return f.good();
}

GameConfiguration::GameConfiguration(const char *jsonFileName)
{
  this->useDefaultConfig = true;

  // Get configuration file name
  if (exists(jsonFileName)) {
    try {
      this->useDefaultConfig = !loadFromFile(jsonFileName);
    } catch (const std::exception &e) {
      logger::Logger::getInstance().logError(
        fmt::format("Configuration file corrupted: {}", e.what()));
    }
  } else {
    logger::Logger::getInstance().logError(fmt::format("Configuration file not found: '{}'", jsonFileName));
  }

  if (this->useDefaultConfig) {
    logger::Logger::getInstance().logInformation("Using default configuration");
    if (this->loadFromFile("default.json")) {
      logger::Logger::getInstance().logInformation(
        "Successfully loaded default configuration");
    } else {
      logger::Logger::getInstance().logError(
        "[FATAL] "
        "Unable to load default configuration");
      throw std::runtime_error("Unable to load default configuration");
    }
  }
}

bool GameConfiguration::loadFromFile(const char *configFileName)
{
  Json::Value jsonRoot;
  {
    std::ifstream jsonFile(configFileName);
    jsonFile >> jsonRoot;
  }
  // Get configuration
  const auto configuration = getJsonValue(jsonRoot, "configuration");

  // Get log
  {
    const auto log = getJsonValue(configuration, "log");

    // Get log level
    const auto logLevelString = getJsonValue(log, "level").asString();
    if (logLevelString == "DEBUG")
      this->logLevel = 2;
    else if (logLevelString == "INFO")
      this->logLevel = 1;
    else
      this->logLevel = 0;
  }

  // Get max players
  this->maxPlayers = getJsonValue(configuration, "players").asLargestUInt();
  if (!(0 < maxPlayers && maxPlayers <= 4)) {
    logger::Logger::getInstance().logError(
      "Number of players must be between 1 and 4");
    return false;
  }

  // Get enemies
  for (const auto &enemy : getJsonValue(getJsonValue(configuration, "game"), "enemies")) {
    if (const auto enemy_quantity = getJsonValue(enemy, "quantity").asInt();
        enemy_quantity < 0) {
      logger::Logger::getInstance().logError(
        "Enemy quantity must be positive or zero");
      return false;
    } else {
      this->enemies.emplace_back(getJsonValue(enemy, "type").asString(),
        enemy_quantity);
    }
  }

  // Get Users
  for (const auto &j : getJsonValue(configuration, "users")) {
    user_t user;

    strcpy(user.username, getJsonValue(j, "username").asCString());
    strcpy(user.password, getJsonValue(j, "password").asCString());

    this->users.emplace_back(user);
  }

  return true;
}

const Json::Value
  GameConfiguration::getJsonValue(const Json::Value &root, std::string name)
{
  const auto value = root[name];
  if (value.empty()) {
    const auto error_message = fmt::format("JSON value not found: '{}'", name);
    logger::Logger::getInstance().logError(error_message);
    throw std::runtime_error(error_message);
  }
  return value;
}
}// namespace configuration
