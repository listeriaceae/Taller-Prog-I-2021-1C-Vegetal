#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <utility>
#include <vector>

namespace logger {
enum class LogLevel;
}

namespace configuration {
void init(const char *configPath);

logger::LogLevel getLogLevel();
unsigned int getMaxPlayers();
std::size_t getFireEnemies();
std::size_t getBarrelFrequency();
std::vector<std::pair<std::string, std::string>> getUsers();
}// namespace configuration

#endif// CONFIGURATION_H
