#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <memory>
#include <fstream>

class Logger {
private:
    static std::unique_ptr<Logger> instance_;  // Declaration
    static std::mutex mutex_;                  // Declaration
    std::ofstream logFile_;

    Logger(const std::string& logFilePath);    // Private constructor

public:
    static Logger* getInstance(const std::string& logFilePath);
    void log(const std::string& message);
};

#endif // LOGGER_H
