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

inline std::atomic<unsigned long long> stackUP1{}; // times stack UP1 was used
inline std::atomic<unsigned long long> stackUP2{}; // times stack UP2 was used
inline std::atomic<unsigned long long> stackDOWN1{}; // times stack DOWN1 was used
inline std::atomic<unsigned long long> stackDOWN2{}; // times stack DOWN

// prints the stats after all games are finished
void print(unsigned long long repetitions, int playerCount);

// increases stackUP1, ... accordingly
void usedStack(unsigned stack);

// to change leftOver stats
void handleLeftOver(const unsigned int& leftOver);

}