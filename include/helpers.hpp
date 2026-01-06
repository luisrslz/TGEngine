#pragma once

#include "player.hpp"

#include <vector>
#include <limits>
#include <iostream>

template <typename T>
T getInput(const T min, const T max) {
    T input;
    std::cin >> input;
    while (input < min || input > max || !std::cin) {
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << config::RED << "ERROR.\n" << config::RESET << "-> ";
        std::cin >> input; 
    }
    return input;
};

// Prints a simple ASCII-Logo
void printLogo();

// Clears the screen and makes Windows-Terminal compatible
void clearScreen();

// Self explanatory
void askPlayerCount(unsigned int &playerCount);

// creates the players, performs initial draw and connects them to the game
std::vector<Player> createPlayers(unsigned int playerCount, Game &game);

// Prints progress of simulations
void printProgress(const unsigned long long& repetitions);