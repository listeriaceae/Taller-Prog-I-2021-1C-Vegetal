#ifndef LOGGER_H
#define LOGGER_H

#include <string_view>

namespace logger {
enum class LogLevel { ERROR, INFO, DEBUG };

void setLogLevel(LogLevel log_level);
void logNewGame(void);
void logGameOver(void);
void log(std::string_view message, std::string_view type);

void logError(std::string_view text);
void logInfo(std::string_view text);
void logDebug(std::string_view text);
};// namespace logger

#endif// LOGGER_H
