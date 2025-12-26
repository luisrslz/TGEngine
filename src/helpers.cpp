#include "helpers.hpp"
#include "config.hpp"
#include <iostream>
#include <limits>

#ifdef _WIN32
#define NOMINMAX // needed sometimes...
#include <windows.h>
#endif // _WIN32

void askPlayerCount(unsigned int &playerCount) {
    std::cout << config::YELLOW << "\nPlease enter the amount of player(s)! (1-" << config::MAX_PLAYERS << ")\n"
              << config::RESET << "-> ";
    std::cin >> playerCount;
    while (playerCount < 1 || playerCount > config::MAX_PLAYERS || !std::cin) {
        handleInputFailure();
        std::cout << config::RED << "ERROR." 
                  << config::YELLOW << "\n\nPlease enter a valid amount! (1-"
                  << config::MAX_PLAYERS << ")\n"
                  << config::RESET << "-> ";
        std::cin >> playerCount;
    }
}

std::vector<Player> createPlayers(unsigned int playerCount, Game &game) {
    std::vector<Player> temp;

    for (size_t i = 0; i < playerCount; ++i) {
        temp.push_back({game});

        // Directly perform initial draw
        temp[i].drawCards();
    }

    return temp;
}


void handleInputFailure() {

    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void clearScreen() {
#ifdef _WIN32
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
    std::cout
        << "/\\/\\ ______________ ______________   ________    _____      _____  ___________ /\\/\\\n"
        << ")/)/ \\__    ___/   |   \\_   _____/  /  _____/   /  _  \\    /     \\ \\_   _____/ )/)\\\n"
        << "       |    | /    ~    \\    __)_  /   \\  ___  /  /_\\  \\  /  \\ /  \\ |    __)_      \n"
        << "       |    | \\    Y    /        \\ \\    \\_\\  \\/    |    \\/    Y    \\|        \\     \n"
        << "       |____|  \\___|_  /_______  /  \\______  /\\____|__  /\\____|__  /_______  /     \n"
        << "                     \\/        \\/          \\/         \\/         \\/        \\/      \n"
        << "             ___________ _______    ________.___ _______  ___________              \n"
        << "             \\_   _____/ \\      \\  /  _____/|   |\\      \\ \\_   _____/              \n"
        << "              |    __)_  /   |   \\/   \\  ___|   |/   |   \\ |    __)_               \n"
        << "              |        \\/    |    \\    \\_\\  \\   /    |    \\|        \\              \n"
        << "             /_______  /\\____|__  /\\______  /___\\____|__  /_______  /              \n"
        << "                     \\/         \\/        \\/            \\/        \\/             \n\n\n";
}