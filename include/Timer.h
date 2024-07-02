#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>
#include <thread> // Includes the library for std::this_thread::get_id
#include <iomanip> // Includes the library for std::put_time
#include <sstream> // Includes the library for std::stringstream

class Timer {
public:
    Timer(const std::string& funcName)
        : funcName(funcName), start(std::chrono::high_resolution_clock::now()) {
        std::cout << "[Profiling] " << funcName << " start at " << getCurrentTime() 
                  << " on thread " << std::this_thread::get_id() << std::endl;
    }

    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "[Profiling] " << funcName << " end at " << getCurrentTime()
                  << " on thread " << std::this_thread::get_id() << std::endl;
        std::cout << "[Profiling] " << funcName << " took " << duration_ms << " milliseconds (" 
                  << duration_us << " microseconds, " << duration_ns << " nanoseconds)" << std::endl;
    }

private:
    std::string funcName;
    std::chrono::high_resolution_clock::time_point start;

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
};

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PROFILE_FUNCTION() Timer MACRO_CONCAT(timer_, __LINE__)(__FUNCTION__);

#endif // TIMER_H
