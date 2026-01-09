#pragma once

#include "game.hpp"
#include "player.hpp"

#include <vector>
#include <thread>

// Game Loop Logic
bool runGameLoop(std::vector<Player> &players, const unsigned int& playerCount, Game &game);

// Simulates {iterations} games with {playerCount} players
void simulate(unsigned long long iterations, const unsigned int playerCount);

// Simulates with multiple threads
void multiThread(std::vector<std::thread>& threads,
                 const unsigned long long& repetitions, const unsigned int& playerCount);

// Simulates with one thread
void singleThread(std::vector<std::thread>& threads,
                  const unsigned long long& repetitions, const unsigned int& playerCount);