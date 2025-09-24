#pragma once

#include "logger.h"

// -------------------------------------------------------------
// Converts a LogLevel enum value to a string representation
// Example: LogLevel::TRACE -> "TRACE"
// -------------------------------------------------------------
static const char *levelToStr(LogLevel lvl) {
  switch (lvl) {
  case LogLevel::TRACE:
    return "TRACE";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARN:
    return "WARN";
  case LogLevel::ERROR:
    return "ERROR";
  default:
    return "UNKNOWN"; // fallback for undefined values
  }
}

// -------------------------------------------------------------
// Returns ANSI color code string for a given LogLevel
// Used for colored console output
// TRACE -> gray, INFO -> green, WARN -> yellow, ERROR -> red
// -------------------------------------------------------------
static const char *levelToColor(LogLevel lvl) {
  switch (lvl) {
  case LogLevel::TRACE:
    return CLR_TRACE;
  case LogLevel::INFO:
    return CLR_INFO;
  case LogLevel::WARN:
    return CLR_WARN;
  case LogLevel::ERROR:
    return CLR_ERROR;
  default:
    return CLR_RESET; // fallback: reset color
  }
}
