#pragma once

#include <string>

// Default values are according to normal card game / instructions
namespace config {

constexpr int DOWN_START = 100; // Determines start value of down counting stack
constexpr int UP_START = 1;     // Determines start value of up counting stack

constexpr int MIN_PLAY = 2;    // Determines how many card a player MUST lay per round
constexpr int MAX_PLAYERS = 5; // Determines how many players are allowed to play

constexpr int PRIVILEGE_RANGE = 3; // If the player has a card within a range of {} to any pile,
                                   // should he perform a extra move?
                                   // Tests showed that 3 leads to highest win-percentage

constexpr int SPECIAL_RULE_DIFF = 10; // Difference for special rule to apply
                                      // -xy for up piles, +xy for down piles

// COLORS
constexpr std::string RED = "\033[0;31m";
constexpr std::string BLUE = "\033[0;34m";
constexpr std::string MAGENTA = "\033[0;35m";
constexpr std::string YELLOW = "\033[0;33m";
constexpr std::string GREEN = "\033[0;32m";
constexpr std::string RESET = "\033[0m";
constexpr std::string CYAN = "\033[0;36m";



// DO NOT CHANGE ----------------------------------------------------
constexpr int HIGHEST_CARD = DOWN_START - 1;
constexpr int LOWEST_CARD = UP_START + 1; 

// Piles with their according index
// Could be an enum CLASS for convention... TODO
enum Stacks {
    UP1, UP2, DOWN1, DOWN2
};

} // namespace config