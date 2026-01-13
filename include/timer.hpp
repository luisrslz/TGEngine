#pragma once

#include <chrono>

// Returns estimated time as string
std::string timeToString(const std::chrono::duration<double>& duration);

// Estimates time for given repetitions and player count
std::string estimateTime(const unsigned long long& repetitions, unsigned int& playerCount);