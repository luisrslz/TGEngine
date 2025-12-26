#pragma once

#include <atomic>

namespace stats {

inline std::atomic<unsigned long long> wins {}; // total wins
inline std::atomic<unsigned long long> losses {}; // total losses
inline std::atomic<unsigned long long> leftOvers{}; // total leftover cards

inline std::atomic<unsigned long long> minLeftOver{}; // best lost game (fewest leftover cards)
inline std::atomic<unsigned long long> maxLeftOver{}; // worst lost game (most leftover cards)

inline std::atomic<unsigned long long> totalRounds{}; // total rounds played

inline std::atomic<unsigned long long> specialMove{}; // total games played


void print(unsigned long long repetitions, int playerCount);

}