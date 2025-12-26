#pragma once

#include "config.hpp"

#include <array>
#include <vector>

class Game {
  public:
    // constructor initializes the stackPile and shuffles it
    Game();

    // simple getter with stackPile.size()
    int stackSize() const;

    // leftOver gets decremented when a card is played -= 1
    void decrementLeftOver();

    // getter for leftOver
    int getLeftOver() const;

    // Removes last card from stackPile and returns it 
    int drawCard();

    // getter for topCards
    std::array<int, 4> getTopCards() const;

    // set topCards.at(pile) = card (after a card is played)
    void setTopCard(int pile, int card);

  private:
    // stack where players draw from
    std::vector<int> stackPile {}; 

    // Up: 0, 1 <---> Down: 2, 3
    // stack / pile on which cards are played 
    std::array<int, 4> topCards{UP_START, UP_START, DOWN_START, DOWN_START};
    
    // How many cards are left, gets defined in constructor
    unsigned int leftOver{};
};
