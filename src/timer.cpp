#include "timer.hpp"
#include "play.hpp"

#include <string>
#include <chrono>
#include <thread>

std::string timeToString(const std::chrono::duration<double>& duration) {
    using namespace std::chrono;

    auto secs = duration_cast<seconds>(duration).count();
    auto mins = secs / 60;
    auto hours_count = mins / 60;

    secs -= mins * 60;
    mins -= hours_count * 60;

    std::string result;
    if (hours_count > 0) {
        result += std::to_string(hours_count) + "h ";
    }
    if (mins > 0 || hours_count > 0) {
        result += std::to_string(mins) + "m ";
    }
    result += std::to_string(secs) + "s";

    return result;
}

std::string estimateTime(const unsigned long long& repetitions, unsigned int& playerCount) {
    constexpr unsigned long long SIMULATION_GAMES = 100000; // should be enough for estimation

    if (repetitions < SIMULATION_GAMES) {
        return "0s";
    }

    double multiplier = static_cast<double>(repetitions) / SIMULATION_GAMES;

    std::vector<std::thread> temp;

    auto start = std::chrono::steady_clock::now();

    multiThread(temp, SIMULATION_GAMES, playerCount);

    for (auto &t : temp) {
        t.join();
    }

    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end - start;

    duration *= multiplier;
    
    return timeToString(duration);
}