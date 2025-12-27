#include "stats.hpp"
#include "config.hpp"

#include <atomic>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream> // needed for macOS

void stats::usedStack(unsigned int stack) {
    switch (stack) {
        case config::UP1:
            ++stackUP1;
            break;
        case config::UP2:
            ++stackUP2;
            break;
        case config::DOWN1:
            ++stackDOWN1;
            break;
        case config::DOWN2:
            ++stackDOWN2;
            break;
        default:
            break;
    }
}

// function to format numbers with commas
// 302492 -> 302,492
std::string formatNumber(unsigned long long number) {
    std::string numStr = std::to_string(number);
    int insertPosition = static_cast<int>(numStr.length()) - 3;
    while (insertPosition > 0) {
        numStr.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    return numStr;
}

std::string formatDouble(double value, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

void printRow(const std::string& label, const std::string& value, const std::string& color = config::RESET) {
    int totalWidth = 46;
    // -4 for 2x "║ " and "  ║"
    int padding = totalWidth - 4 - label.length() - value.length();

    if (padding < 0) {
        padding = 0; // prevent negative padding
    }

    std::cout << "║  " << color << label 
              << std::string(padding, ' ') // dynamic padding
              << value << config::RESET << "  ║\n";
}

void printSeparator() {
        std::cout << "╠══════════════════════════════════════════════╣\n";
}

void stats::handleLeftOver(const unsigned int& leftOver) {
    leftOvers += leftOver;

    // update minLeftOver thread-safely
    if (leftOver != 0) {
        unsigned long long currentMin = minLeftOver.load(std::memory_order_relaxed);
        while (leftOver < currentMin) {
            if (minLeftOver.compare_exchange_weak(
                    currentMin, leftOver, 
                    std::memory_order_relaxed, 
                    std::memory_order_relaxed)) {
                break;
            }
        }
    }
    
    // update maxLeftOver thread-safely
    unsigned long long currentMax = maxLeftOver.load(std::memory_order_relaxed);
    while (leftOver > currentMax) {
        if (maxLeftOver.compare_exchange_weak(
                currentMax, leftOver, 
                std::memory_order_relaxed, 
                std::memory_order_relaxed)) {
            break;
        }
    }
}

std::string stats::mostUsedStack() {
    unsigned long long maxUses = 0;
    std::string mostUsed;

    if (stackUP1 > maxUses) {
        maxUses = stackUP1;
        mostUsed = "UP1";
    }
    if (stackUP2 > maxUses) {
        maxUses = stackUP2;
        mostUsed = "UP2";
    }
    if (stackDOWN1 > maxUses) {
        maxUses = stackDOWN1;
        mostUsed = "DOWN1";
    }
    if (stackDOWN2 > maxUses) {
        maxUses = stackDOWN2;
        mostUsed = "DOWN2";
    }

    return mostUsed + " (" + formatNumber(maxUses) + " uses)";
}

void stats::print(unsigned long long repetitions, int playerCount) {
    double winRate = static_cast<double>(wins) / (wins + losses) * 100.0;
    double lossRate = static_cast<double>(losses) / (wins + losses) * 100.0;
    double avgLeftOver = static_cast<double>(leftOvers) / (wins + losses);

    if (minLeftOver == std::numeric_limits<unsigned long long>::max()) {
        minLeftOver = 0; // prevent print of max value if no losses occurred
    }

    std::string stack = mostUsedStack();

    std::cout << "\n\n"  << std::fixed << std::setprecision(2);
    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║" << config::BLUE << "             SIMULATION RESULTS               " << config::RESET << "║\n";
    printSeparator();
    printRow("Players: ", std::to_string(playerCount), config::BLUE);
    printRow("Total Games:", formatNumber(repetitions), config::BLUE);
    printSeparator();
    printRow("Wins:", formatNumber(wins), config::GREEN);
    printRow("Losses:", formatNumber(losses), config::RED);
    printRow("Win Rate:", formatDouble(winRate) + " %", config::GREEN);
    printRow("Loss Rate:", formatDouble(lossRate) + " %", config::RED);
    printSeparator();
    printRow("Total Rounds:", formatNumber(totalRounds), config::CYAN);
    printRow("Avg Rounds/Game:", formatDouble(static_cast<double>(totalRounds) / repetitions), config::CYAN);
    printRow("Avg Leftover Cards/Game:", formatDouble(avgLeftOver), config::CYAN);
    printRow("Best Lost Game (fewest):", formatNumber(minLeftOver), config::YELLOW);
    printRow("Worst Lost Game (most):", formatNumber(maxLeftOver), config::RED);
    printSeparator();
    printRow("Most Used Stack:", stack, config::BLUE);
    printRow("Average special moves/Game:", formatDouble(static_cast<double>(specialMove) / repetitions), config::BLUE);
    std::cout << "╚══════════════════════════════════════════════╝\n";
    
}