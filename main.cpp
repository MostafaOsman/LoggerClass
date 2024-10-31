#include "Logger.h"
#include <thread>
#include <vector>

void threadFunction(int id) {
    Logger* logger = Logger::getInstance("log.txt");
    for (int i = 0; i < 10; ++i) {
        logger->log("Thread " + std::to_string(id) + " - Message " + std::to_string(i));
    }
}

int main() {
    std::vector<std::thread> threads;

    // Start multiple threads
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(threadFunction, i);
    }

    // Join all threads to ensure they complete before main exits
    for (auto& thread : threads) {
        thread.join();
    }

    return 0; // It's a good practice to return an integer from main
}
