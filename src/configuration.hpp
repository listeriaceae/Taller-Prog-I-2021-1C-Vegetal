#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>
#include <json/json.h>
#include "utils/user.hpp"

namespace configuration {
class Enemy
{
public:
  Enemy(const std::string &t, unsigned int q) : type{ t }, quantity{ q } {}
  Enemy(std::string &&t, unsigned int q) noexcept
    : type{ std::move(t) }, quantity{ q }
  {}

  const std::string &getType() const & { return type; }
  std::string getType() const && { return type; }
  unsigned int getQuantity() const { return quantity; }

private:
  std::string type;
  unsigned int quantity;
};

class GameConfiguration
{
public:
  static const GameConfiguration &getInstance(const char *json_filename);

  int getLogLevel() const { return logLevel; }
  const std::vector<user_t> &getUsers() const & { return users; }
  std::vector<user_t> getUsers() const && { return users; }
  const std::vector<configuration::Enemy> &getEnemies() const &
  {
    return enemies;
  }
  std::vector<configuration::Enemy> getEnemies() const && { return enemies; }
  std::size_t getMaxPlayers() const { return maxPlayers; }
  bool getDefaultConfigFlag() const { return useDefaultConfig; }

private:
  GameConfiguration(const char *json_filename);
  int logLevel;
  std::vector<user_t> users;
  std::vector<Enemy> enemies;
  std::size_t maxPlayers;
  bool useDefaultConfig;

  static const Json::Value getJsonValue(const Json::Value &root,
    std::string name);
  bool loadFromFile(const char *configFileName);
};
}// namespace configuration

#endif// CONFIGURATION_H
