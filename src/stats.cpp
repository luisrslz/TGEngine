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

std::string formatDouble(double value, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

void printRow(const std::string& label, const std::string& value, const     std::string& color = config::RESET) {
    int totalWidth = 42;
    // -4 for 2x "║ " and "  ║"
    int padding = totalWidth - 4 - label.length() - value.length();


std::cout << "║  " << color << label
              << std::string(padding, ' ') // dynamic padding
<< value << config::RESET << "  ║\n";
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

}