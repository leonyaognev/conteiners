#pragma once

// -------------------------------------------------------------
// Log levels enumeration
// -------------------------------------------------------------
enum class LogLevel { TRACE, INFO, WARN, ERROR };

// -------------------------------------------------------------
// Default log file name
// -------------------------------------------------------------
#define LOG_FILE "app.log"

// -------------------------------------------------------------
// ANSI color codes for console output
// TRACE  -> gray
// INFO   -> green
// WARN   -> yellow
// ERROR  -> red
// CLR_RESET resets console color
// -------------------------------------------------------------
#define CLR_TRACE "\033[90m"
#define CLR_INFO "\033[32m"
#define CLR_WARN "\033[33m"
#define CLR_ERROR "\033[31m"
#define CLR_RESET "\033[0m"

// -------------------------------------------------------------
// Main logging function
// level - log level (TRACE, INFO, WARN, ERROR)
// file  - source file name (__FILE__)
// func  - function name (__func__)
// line  - line number (__LINE__)
// fmt   - printf-style format string
// -------------------------------------------------------------
void logMessage(LogLevel lvl, const char *file, const char *func, int line,
                const char *fmt, ...);

// -------------------------------------------------------------
// Logging macros
// If DEBUG is defined, these macros call logMessage() with
// the correct level, file, function, and line information.
// Otherwise, they expand to nothing, effectively disabling logging.
// -------------------------------------------------------------
#if DEBUG_LEVEL >= 4
#define log_trace(fmt, ...)                                                    \
  logMessage(LogLevel::TRACE, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define log_trace(fmt, ...) ((void)0)
#endif

#if DEBUG_LEVEL >= 3
#define log_info(fmt, ...)                                                     \
  logMessage(LogLevel::INFO, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define log_info(fmt, ...) ((void)0)
#endif

#if DEBUG_LEVEL >= 2
#define log_warn(fmt, ...)                                                     \
  logMessage(LogLevel::WARN, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define log_warn(fmt, ...) ((void)0)
#endif

#if DEBUG_LEVEL >= 1
#define log_error(fmt, ...)                                                    \
  logMessage(LogLevel::ERROR, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define log_error(fmt, ...) ((void)0)
#endif
