#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>
#include <thread> // Includes the library for std::this_thread::get_id
#include <iomanip> // Includes the library for std::put_time
#include <sstream> // Includes the library for std::stringstream
#include <fstream> // Includes the library for file output
#include <memory> // Includes the library for std::shared_ptr

/**
 * @brief Timer class for profiling function execution time.
 * 
 * This class measures the time taken by a function from its creation to its destruction.
 * It logs the start time, end time, duration, and optionally writes the logs to a file.
 */
class Timer {
public:
    /**
     * @brief Constructs a Timer object and logs the start time.
     * 
     * @param funcName The name of the function being profiled.
     * @param logToFile Indicates whether to log the profiling information to a file.
     */
    Timer(const std::string& funcName, bool logToFile = false)
        : funcName(funcName), start(std::chrono::high_resolution_clock::now()), logToFile(logToFile) {
        log("[Profiling] " + funcName + " start at " + getCurrentTime() 
            + " on thread " + getThreadId());
    }

    /**
     * @brief Destructs the Timer object and logs the end time and duration.
     */
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        log("[Profiling] " + funcName + " end at " + getCurrentTime()
            + " on thread " + getThreadId());
        log("[Profiling] " + funcName + " took " + std::to_string(duration_ms) + " milliseconds (" 
            + std::to_string(duration_us) + " microseconds, " + std::to_string(duration_ns) + " nanoseconds)");
    }

private:
    std::string funcName;
    std::chrono::high_resolution_clock::time_point start;
    bool logToFile;

    /**
     * @brief Get the current time as a formatted string.
     * 
     * @return std::string The current time in HH:MM:SS.sss format.
     */
    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_time), "%T") << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }

    /**
     * @brief Get the current thread ID as a string.
     * 
     * @return std::string The current thread ID.
     */
    std::string getThreadId() {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        return ss.str();
    }

    /**
     * @brief Log a message to the console or a file.
     * 
     * @param message The message to log.
     */
    void log(const std::string& message) {
        if (logToFile) {
            static std::shared_ptr<std::ofstream> logFile = std::make_shared<std::ofstream>("profiling.log", std::ios::app);
            *logFile << message << std::endl;
        } else {
            std::cout << message << std::endl;
        }
    }
};

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PROFILE_FUNCTION() Timer MACRO_CONCAT(timer_, __LINE__)(__FUNCTION__);
#define PROFILE_FUNCTION_TO_FILE() Timer MACRO_CONCAT(timer_, __LINE__)(__FUNCTION__, true);

#endif // TIMER_H
