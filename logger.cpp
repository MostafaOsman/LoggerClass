#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <memory>

class Logger {
private:
    static std::mutex mutex_;
    static std::unique_ptr<Logger> instance_;
    std::ofstream logFile_;

    // Private constructor to prevent instantiation
    Logger(const std::string& logFilePath) {
        logFile_.open(logFilePath, std::ios::app);
    }

public:
    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Destructor to close file
    ~Logger() {
        if (logFile_.is_open()) {
            logFile_.close();
        }
    }

    // Static method for accessing class instance
    static Logger* getInstance(const std::string& logFilePath) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_ = std::unique_ptr<Logger>(new Logger(logFilePath));
        }
        return instance_.get();
    }

    // Method to log a message
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logFile_.is_open()) {
            logFile_ << message << std::endl;
        }
    }
};

// Initialize static members
std::mutex Logger::mutex_;
std::unique_ptr<Logger> Logger::instance_ = nullptr;
