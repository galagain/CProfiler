#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>

class Timer {
public:
    Timer(const std::string& funcName)
        : funcName(funcName), start(std::chrono::high_resolution_clock::now()) {
        std::cout << "[Profiling] " << funcName << " start" << std::endl;
    }

    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "[Profiling] " << funcName << " took " << duration_us << " microseconds (" << duration_ns << " nanoseconds)" << std::endl;
    }

private:
    std::string funcName;
    std::chrono::high_resolution_clock::time_point start;
};

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PROFILE_FUNCTION() Timer MACRO_CONCAT(timer_, __LINE__)(__FUNCTION__);

#endif // TIMER_H