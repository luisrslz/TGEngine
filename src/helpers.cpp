#include "helpers.hpp"
#include "stats.hpp"
#include <iostream>

#ifdef _WIN32
#define NOMINMAX // needed sometimes...
#include <windows.h>
#endif // _WIN32

std::vector<Player> createPlayers(unsigned int playerCount, Game &game) {
    std::vector<Player> temp;

    for (size_t i = 0; i < playerCount; ++i) {
        temp.push_back({game});

        // Directly perform initial draw
        temp[i].drawCards();
    }

    return temp;
}

void printProgress(const unsigned long long& repetitions) {
    // Width = 41 to align with output box
    const int barWidth = 41;

    unsigned long long done = stats::wins.load() + stats::losses.load();
    double progress = static_cast<double>(done) / repetitions;
    int pos = static_cast<int>(barWidth * progress);
    std::cout << "\r["; // start of bar
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) {
            std::cout << "=";
        } else if (i == pos) {
            std::cout << ">";
        } else {
            std::cout << " ";
        }
    }
    // Flush ensures equal output speed on all OS's
    std::cout << "] " << int(progress * 100.0) << "%" << std::flush;
}

void clearScreen() {
#ifdef _WIN32
    // utf-8 output 
    SetConsoleOutputCP(CP_UTF8);

    // makes windows-terminal compatible with colors
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }
#endif // _WIN32

    // Clear the terminal
    std::cout << "\033[2J\033[1;1H";
}

void printLogo() {
    std::cout << "Welcome to \"THE GAME\"-Engine.\n"
              << "A fast, multithreaded C++ engine for simulating the card game \"The Game\"\n"
              << "(originally created by Steffen Benndorf and published by NSV).\n";
}