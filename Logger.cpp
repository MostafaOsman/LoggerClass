#include "Logger.h"

// Define static members
std::unique_ptr<Logger> Logger::instance_; // Definition
std::mutex Logger::mutex_;                 // Definition

// Initialize static members
Logger::Logger(const std::string& logFilePath) {
    logFile_.open(logFilePath, std::ios::app);  // Open the log file in append mode
    if (!logFile_.is_open()) {
        throw std::runtime_error("Unable to open log file.");
    }
}

Logger* Logger::getInstance(const std::string& logFilePath) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance_ == nullptr) {
        instance_ = std::unique_ptr<Logger>(new Logger(logFilePath));
    }
    return instance_.get();
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logFile_.is_open()) {
        logFile_ << message << std::endl;
    }
}
