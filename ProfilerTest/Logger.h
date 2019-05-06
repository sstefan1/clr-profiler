#pragma once
#pragma warning ( disable: 4996 )
#define _CRT_SECURE_NO_WARNINGS
//===- Logger/Log.h - Simple logger class -----------------------*- C++ -*-===//
//
// This file defines LogLine class.
// It is only intended to be used within this project and is header only.
//
//===----------------------------------------------------------------------===//

#ifndef LOG_H
#define LOG_H

// #include <Utils/Utils.h>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>


//#define LOG(LEVEL)                                                             \
//  logger::LogLine(logger::Level::LEVEL, "log.txt", __FILE__, __FUNCTION__,     \
//                  __LINE__)

#define LOG(LEVEL)                                                             \
  logger::LogLine(logger::Level::LEVEL, "F:\\projects\\profiler\\log.txt", __FILE__, __FUNCTION__,     \
                  __LINE__)
namespace logger {

/// Returns pointer to a static internal std::tm object. This function should
/// only be used as an argument to std::put_time() function for stream
/// manipulation.
/// usage: std::put_time(utils::GetTimeStamp(), "%T") // %T -> hh:mm:ss
std::tm *GetTimestamp() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_c =
      std::chrono::system_clock::to_time_t(now); // - std::chrono::hours(24));
  std::tm *localtime = std::localtime(&now_c);

  return localtime;
}

enum class Level : uint8_t { DEBUG, INFO, WARN, ERR };

class LogLine {
public:
  LogLine(Level level, std::string filename, const char *file,
          const char *function, int line)
      : out(filename, std::ios::app), level(level), file(file),
        function(function), line(line) {
    auto timestamp = GetTimestamp();
    ss << '[' << std::put_time(timestamp, "%D %T") << "] | " << file << ":"
       << function << ":" << line << " " << getLevel() << " | ";
  }

  ~LogLine() {
    ss << "\n";
    out << ss.rdbuf();
    out.flush();
  }

  template <typename T> LogLine &operator<<(const T &thing) {
    ss << thing;
    return *this;
  }

private:
  std::stringstream ss;
  std::ofstream out;
  Level level;
  const char *file, *function;
  int line;

  const char *getLevel() {
    switch (level) {
    case Level::DEBUG:
      return "[DEBUG]";
      break;
    case Level::INFO:
      return "[INFO]";
      break;
    case Level::WARN:
      return "[WARNING]";
      break;
    case Level::ERR:
	default:
      return "[ERROR]";
	  break;
    }
  }
};

} // namespace logger

#endif // LOG_H
