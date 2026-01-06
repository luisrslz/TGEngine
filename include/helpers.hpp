#pragma once

#include "player.hpp"

#include <vector>

// Handles cin errors
void handleInputFailure();

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