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

std::vector<Player> createPlayers(unsigned int playerCount, Game &game);

