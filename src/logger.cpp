#include <fstream>
#include <chrono>
#include "logger.hpp"

namespace logger {
Logger &Logger::getInstance()
{
  static Logger instance{};
  return instance;
}

void Logger::log(std::string_view message, std::string_view type) const
{
  char mbstr[20];
  auto current_time =
    std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  strftime(mbstr, sizeof mbstr, "%Y-%m-%d %X", std::localtime(&current_time));

  std::ofstream file(filepath.data(), std::ofstream::app);
  file << mbstr << type << message << std::endl;
}

void Logger::logNewGame(void) const
{
  logInformation(R"(
-------------------------
 STARTING DONKEY KONG II
-------------------------)");
}

void Logger::logGameOver(void) const
{
  logInformation(R"(
-------------------------
  ENDING DONKEY KONG II
-------------------------)");
}
}// namespace logger
