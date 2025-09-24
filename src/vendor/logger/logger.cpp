#include <atomic>
#include <condition_variable>
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "levelTo.h"
#include "logger.h"

struct LogTask {
  LogLevel level;
  std::string file;
  std::string func;
  int line;
  std::string message;
  std::string timestamp;
};

class AsyncLogger {
public:
  AsyncLogger(const std::string &filePath)
      : stopFlag(false), logFile(filePath, std::ios::app) {
    worker = std::thread(&AsyncLogger::processQueue, this);
  }

  ~AsyncLogger() {
    {
      std::lock_guard<std::mutex> lock(queueMutex);
      stopFlag = true;
    }
    cv.notify_one();
    if (worker.joinable())
      worker.join();
    logFile.close();
  }

  void log(LogLevel level, const char *file, const char *func, int line,
           const char *fmt, va_list args) {
    char buf[1024];
    vsnprintf(buf, sizeof(buf), fmt, args);

    // timestamp
    std::time_t t = std::time(nullptr);
    std::tm tm_info{};
    localtime_r(&t, &tm_info);
    char timeBuf[20];
    std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", &tm_info);

    LogTask task{level, file, func, line, buf, timeBuf};

    {
      std::lock_guard<std::mutex> lock(queueMutex);
      queue.push(std::move(task));
    }
    cv.notify_one();
  }

private:
  void processQueue() {
    while (true) {
      std::unique_lock<std::mutex> lock(queueMutex);
      cv.wait(lock, [this] { return !queue.empty() || stopFlag; });

      if (stopFlag && queue.empty())
        break;

      LogTask task = std::move(queue.front());
      queue.pop();
      lock.unlock();

      // console output
      std::cout << levelToColor(task.level) << "[" << levelToStr(task.level)
                << "] " << CLR_RESET << task.timestamp << " " << task.file
                << ":" << task.line << " " << task.func
                << "(): " << task.message << std::endl;

      // file output
      if (logFile.is_open()) {
        logFile << "[" << levelToStr(task.level) << "] " << task.timestamp
                << " " << task.file << ":" << task.line << " " << task.func
                << "(): " << task.message << std::endl;
      }
    }
  }

  std::mutex queueMutex;
  std::condition_variable cv;
  std::queue<LogTask> queue;
  std::thread worker;
  std::atomic<bool> stopFlag;
  std::ofstream logFile;
};

// --- global logger instance ---
static AsyncLogger g_logger(LOG_FILE);

void logMessage(LogLevel level, const char *file, const char *func, int line,
                const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  g_logger.log(level, file, func, line, fmt, args);
  va_end(args);
}
