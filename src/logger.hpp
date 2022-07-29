#ifndef LOGGER_H
#define LOGGER_H

#include <string_view>

namespace logger {
class Logger
{
private:
  Logger() = default;
  ~Logger() = default;
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  std::string_view filepath{ "game.log" };
  int log_level{};

  void log(std::string_view message, std::string_view type) const;

public:
  static Logger &getInstance();
  void setLogLevel(int log_level_) { this->log_level = log_level_; }
  void logNewGame(void) const;
  void logGameOver(void) const;
  inline void logError(std::string_view text) const { log(text, "[ERROR]"); }
  inline void logInformation(std::string_view text) const
  {
    if (log_level >= 1) log(text, "[INFO]");
  }
  inline void logDebug(std::string_view text) const
  {
    if (log_level >= 2) log(text, "[DEBUG]");
  }
};
}// namespace logger

#endif// LOGGER_H
