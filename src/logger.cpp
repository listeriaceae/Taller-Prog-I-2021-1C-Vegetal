#include <fstream>
#include <chrono>
#include "logger.hpp"

namespace logger {
static LogLevel log_level{ LogLevel::ERROR };

void
setLogLevel(LogLevel ll)
{
  log_level = ll;
}

void
log(std::string_view message, std::string_view type)
{
  char mbstr[20];
  auto current_time =
    std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  strftime(mbstr, sizeof mbstr, "%Y-%m-%d %X", std::localtime(&current_time));

  std::ofstream file("game.log", std::ofstream::app);
  file << mbstr << type << message << std::endl;
}

void
logNewGame(void)
{
  logInfo(R"(
-------------------------
 STARTING DONKEY KONG II
-------------------------)");
}

void
logGameOver(void)
{
  logInfo(R"(
-------------------------
  ENDING DONKEY KONG II
-------------------------)");
}

void
logError(std::string_view text)
{
  log(text, "[ERROR]");
}

void
logInfo(std::string_view text)
{
  if (log_level >= LogLevel::INFO)
    log(text, "[INFO]");
}

void
logDebug(std::string_view text)
{
  if (log_level >= LogLevel::DEBUG)
    log(text, "[DEBUG]");
}
}
// namespace logger
