#include "stats.hpp"
#include "config.hpp"

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
// source: copied from internet
std::string formatNumber(unsigned long long number) {
    std::string numStr = std::to_string(number);
    int insertPosition = static_cast<int>(numStr.length()) - 3;
    while (insertPosition > 0) {
        numStr.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    return numStr;
}

void printRow(const std::string& label, const std::string& value) {
    std::cout << "║  " << std::left << std:: setw(18) << label
              << std::right << std::setw(22) << value << "  ║\n";
}

void printSeparator() {
        std::cout << "╠══════════════════════════════════════════╣\n";
}

void stats::handleLeftOver(const unsigned int& leftOver) {
    leftOvers += leftOver;

    if (leftOver < minLeftOver && leftOver != 0) {
        minLeftOver = leftOver;
    }
    
    if (leftOver > maxLeftOver) {
        maxLeftOver = leftOver;
    }
}

void stats::print(unsigned long long repetitions, int playerCount) {
    double winRate = static_cast<double>(wins) / (wins + losses) * 100.0;
    double lossRate = static_cast<double>(losses) / (wins + losses) * 100.0;
    double avgLeftOver = static_cast<double>(leftOvers) / (wins + losses);

}